#!/usr/bin/env python3
"""OpenCV lane detector for the integrated V2X/Nav2/MPPI stack.

This is adapted from qcar-master/lane_keeping, but it is intentionally
perception-only. It publishes lane pixels and optional debug masks; it does not
publish Twist and therefore cannot fight Nav2, MPPI, or the priority mux.
"""

import cv2
import numpy as np
import rclpy
from cv_bridge import CvBridge
from geometry_msgs.msg import Point32
from rclpy.node import Node
from sensor_msgs.msg import Image

WHITE_LOWER = np.array([0, 0, 180])
WHITE_UPPER = np.array([180, 60, 255])
YELLOW_LOWER = np.array([15, 80, 120])
YELLOW_UPPER = np.array([35, 255, 255])
ROI_TOP_FRACTION = 0.55
SRC_TOP_LEFT_FRAC = (0.30, 0.55)
SRC_TOP_RIGHT_FRAC = (0.70, 0.55)
SRC_BOTTOM_LEFT_FRAC = (0.05, 1.00)
SRC_BOTTOM_RIGHT_FRAC = (0.95, 1.00)
MIN_LANE_PIXELS = 50
N_WINDOWS = 9
WINDOW_MARGIN = 60
MIN_PIXELS_RECENTER = 40


class LaneDetectionNode(Node):
    def __init__(self):
        super().__init__('lane_detection_node')
        self.declare_parameter('camera_topic', '/qcar/camera/image_raw')
        self.declare_parameter('lane_pixel_topic', '/v2x/opencv/lane_pixels')
        self.declare_parameter('debug_mask_topic', '/v2x/opencv/lane_mask')
        self.declare_parameter('publish_debug_mask', False)

        self.bridge = CvBridge()
        self._warp_matrix = None
        self._warp_size = None
        self._last_center_x = None

        camera_topic = self.get_parameter('camera_topic').value
        lane_topic = self.get_parameter('lane_pixel_topic').value
        self.create_subscription(Image, camera_topic, self.image_callback, 10)
        self.lane_pub = self.create_publisher(Point32, lane_topic, 10)
        self.debug_pub = self.create_publisher(Image, self.get_parameter('debug_mask_topic').value, 10)

        self.get_logger().info(
            f'OpenCV lane perception ready: {camera_topic} -> {lane_topic}. '
            'No /cmd_vel output is produced by this node.'
        )

    def image_callback(self, msg: Image):
        try:
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as exc:
            self.get_logger().warn(f'CvBridge conversion failed: {exc}')
            return

        height, width = frame.shape[:2]
        roi_top_px = int(height * ROI_TOP_FRACTION)
        roi = frame[roi_top_px:height, 0:width]
        roi_h, roi_w = roi.shape[:2]

        hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        mask_white = cv2.inRange(hsv, WHITE_LOWER, WHITE_UPPER)
        mask_yellow = cv2.inRange(hsv, YELLOW_LOWER, YELLOW_UPPER)
        mask = cv2.bitwise_or(mask_white, mask_yellow)
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
        warped = self._warp_to_birdseye(mask, roi_w, roi_h)

        center_x, found = self._extract_centerline(warped)
        if not found:
            if self._last_center_x is None:
                self.get_logger().warn('No lane pixels detected; skipping publish', throttle_duration_sec=2.0)
                return
            center_x = self._last_center_x
        self._last_center_x = center_x

        point = Point32()
        point.x = float(center_x)
        point.y = float(roi_h)
        point.z = 1.0 if found else 0.5  # simple confidence marker
        self.lane_pub.publish(point)

        if bool(self.get_parameter('publish_debug_mask').value):
            try:
                self.debug_pub.publish(self.bridge.cv2_to_imgmsg(warped, encoding='mono8'))
            except Exception as exc:
                self.get_logger().warn(f'Debug mask publish failed: {exc}', throttle_duration_sec=2.0)

    def _warp_to_birdseye(self, mask, w, h):
        if self._warp_matrix is None or self._warp_size != (w, h):
            src = np.float32([
                [w * SRC_TOP_LEFT_FRAC[0], h * SRC_TOP_LEFT_FRAC[1]],
                [w * SRC_TOP_RIGHT_FRAC[0], h * SRC_TOP_RIGHT_FRAC[1]],
                [w * SRC_BOTTOM_RIGHT_FRAC[0], h * SRC_BOTTOM_RIGHT_FRAC[1]],
                [w * SRC_BOTTOM_LEFT_FRAC[0], h * SRC_BOTTOM_LEFT_FRAC[1]],
            ])
            dst = np.float32([[0, 0], [w, 0], [w, h], [0, h]])
            self._warp_matrix = cv2.getPerspectiveTransform(src, dst)
            self._warp_size = (w, h)
        return cv2.warpPerspective(mask, self._warp_matrix, (w, h))

    def _extract_centerline(self, warped):
        h, w = warped.shape[:2]
        histogram = np.sum(warped[h // 2:, :], axis=0)
        midpoint = w // 2
        left_base = int(np.argmax(histogram[:midpoint]))
        right_base = int(np.argmax(histogram[midpoint:]) + midpoint)
        left_has_signal = histogram[left_base] > MIN_LANE_PIXELS
        right_has_signal = histogram[right_base] > MIN_LANE_PIXELS
        if not left_has_signal and not right_has_signal:
            return None, False

        window_height = h // N_WINDOWS
        nonzero_y, nonzero_x = warped.nonzero()
        nonzero_y = np.array(nonzero_y)
        nonzero_x = np.array(nonzero_x)
        left_current = left_base
        right_current = right_base
        left_pixels_x = []
        right_pixels_x = []

        for window in range(N_WINDOWS):
            y_low = h - (window + 1) * window_height
            y_high = h - window * window_height
            if left_has_signal:
                good = ((nonzero_y >= y_low) & (nonzero_y < y_high) &
                        (nonzero_x >= left_current - WINDOW_MARGIN) &
                        (nonzero_x < left_current + WINDOW_MARGIN)).nonzero()[0]
                if len(good) > 0:
                    left_pixels_x.extend(nonzero_x[good])
                if len(good) > MIN_PIXELS_RECENTER:
                    left_current = int(np.mean(nonzero_x[good]))
            if right_has_signal:
                good = ((nonzero_y >= y_low) & (nonzero_y < y_high) &
                        (nonzero_x >= right_current - WINDOW_MARGIN) &
                        (nonzero_x < right_current + WINDOW_MARGIN)).nonzero()[0]
                if len(good) > 0:
                    right_pixels_x.extend(nonzero_x[good])
                if len(good) > MIN_PIXELS_RECENTER:
                    right_current = int(np.mean(nonzero_x[good]))

        if left_has_signal and right_has_signal:
            left_mean = np.mean(left_pixels_x) if left_pixels_x else left_base
            right_mean = np.mean(right_pixels_x) if right_pixels_x else right_base
            center_x = (left_mean + right_mean) / 2.0
        elif left_has_signal:
            left_mean = np.mean(left_pixels_x) if left_pixels_x else left_base
            center_x = left_mean + (w * 0.5) / 2.0
        else:
            right_mean = np.mean(right_pixels_x) if right_pixels_x else right_base
            center_x = right_mean - (w * 0.5) / 2.0
        return float(center_x), True


def main(args=None):
    rclpy.init(args=args)
    node = LaneDetectionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
