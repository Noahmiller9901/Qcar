#!/usr/bin/env python3
"""Convert lane pixel detections into planner-friendly advisory topics.

This node is the conflict-free replacement for the old lane_keeping_node.py.
It does not drive the robot. It publishes a small Path in base_link and a JSON
status payload that can later be consumed by a Nav2 costmap/plugin or custom
cost-planning node.
"""

import json

import rclpy
from geometry_msgs.msg import Point32, PoseStamped
from nav_msgs.msg import Path
from rclpy.node import Node
from std_msgs.msg import String


class LanePathAdapterNode(Node):
    def __init__(self):
        super().__init__('lane_path_adapter_node')
        self.declare_parameter('lane_pixel_topic', '/v2x/opencv/lane_pixels')
        self.declare_parameter('lane_path_topic', '/v2x/opencv/lane_centerline_path')
        self.declare_parameter('lane_status_topic', '/v2x/opencv/lane_status')
        self.declare_parameter('camera_width_px', 640.0)
        self.declare_parameter('meters_per_pixel', 0.003)
        self.declare_parameter('frame_id', 'base_link')
        self.declare_parameter('path_length_m', 3.0)
        self.declare_parameter('path_points', 12)

        self.create_subscription(Point32, self.get_parameter('lane_pixel_topic').value, self.on_lane_pixel, 10)
        self.path_pub = self.create_publisher(Path, self.get_parameter('lane_path_topic').value, 10)
        self.status_pub = self.create_publisher(String, self.get_parameter('lane_status_topic').value, 10)
        self.get_logger().info(
            'Lane path adapter ready. Output is advisory perception only; no Twist commands are published.'
        )

    def on_lane_pixel(self, msg: Point32):
        width = float(self.get_parameter('camera_width_px').value)
        m_per_px = float(self.get_parameter('meters_per_pixel').value)
        frame_id = str(self.get_parameter('frame_id').value)
        lateral_error_m = (msg.x - width / 2.0) * m_per_px
        confidence = float(msg.z)

        path = Path()
        path.header.stamp = self.get_clock().now().to_msg()
        path.header.frame_id = frame_id
        n = max(2, int(self.get_parameter('path_points').value))
        length = float(self.get_parameter('path_length_m').value)
        for i in range(n):
            ratio = i / float(n - 1)
            pose = PoseStamped()
            pose.header = path.header
            pose.pose.position.x = ratio * length
            pose.pose.position.y = -lateral_error_m * (1.0 - 0.35 * ratio)
            pose.pose.position.z = 0.0
            pose.pose.orientation.w = 1.0
            path.poses.append(pose)
        self.path_pub.publish(path)

        status = {
            'source': 'opencv_lane_detection',
            'lane_center_px': round(float(msg.x), 2),
            'image_width_px': width,
            'lateral_error_m': round(lateral_error_m, 4),
            'confidence': confidence,
            'intended_consumer': 'Nav2 costmap/planner or custom cost planner',
            'direct_control': False,
        }
        out = String()
        out.data = json.dumps(status)
        self.status_pub.publish(out)


def main(args=None):
    rclpy.init(args=args)
    node = LanePathAdapterNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
