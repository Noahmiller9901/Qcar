#!/usr/bin/env python3
"""Plan B path generator.

Inputs:
  /odom                              current pose
  /scan                              simple obstacle awareness
  /v2x/opencv/lane_centerline_path   preferred OpenCV/lane reference
  /v2x/signal_status                 traffic-light state

Output:
  /v2x/raw_path                      local path in odom frame

This is intentionally lightweight. It produces a demo-safe local path that can
follow the OpenCV lane reference when available, otherwise it produces a forward
path with a simple lateral detour if scan obstacles are directly ahead.
"""

import json
import math
from typing import Optional

import rclpy
from nav_msgs.msg import Odometry, Path
from geometry_msgs.msg import PoseStamped
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String

from .common import yaw_from_quaternion, quaternion_from_yaw, clamp


class CustomPathPlannerNode(Node):
    def __init__(self):
        super().__init__('custom_path_planner_node')
        self.declare_parameter('odom_topic', '/odom')
        self.declare_parameter('scan_topic', '/scan')
        self.declare_parameter('lane_path_topic', '/v2x/opencv/lane_centerline_path')
        self.declare_parameter('signal_topic', '/v2x/signal_status')
        self.declare_parameter('raw_path_topic', '/v2x/raw_path')
        self.declare_parameter('output_frame_id', 'odom')
        self.declare_parameter('publish_rate_hz', 10.0)
        self.declare_parameter('path_length_m', 8.0)
        self.declare_parameter('path_points', 36)
        self.declare_parameter('lane_timeout_sec', 1.0)
        self.declare_parameter('obstacle_front_width_m', 1.1)
        self.declare_parameter('obstacle_front_distance_m', 2.5)
        self.declare_parameter('detour_lateral_m', 1.2)
        self.declare_parameter('stop_on_red_yellow', True)

        self.odom: Optional[Odometry] = None
        self.scan: Optional[LaserScan] = None
        self.lane_path: Optional[Path] = None
        self.lane_stamp = None
        self.signal_phase = 'UNKNOWN'

        self.create_subscription(Odometry, self.get_parameter('odom_topic').value, self.on_odom, 20)
        self.create_subscription(LaserScan, self.get_parameter('scan_topic').value, self.on_scan, 10)
        self.create_subscription(Path, self.get_parameter('lane_path_topic').value, self.on_lane_path, 10)
        self.create_subscription(String, self.get_parameter('signal_topic').value, self.on_signal, 10)
        self.pub = self.create_publisher(Path, self.get_parameter('raw_path_topic').value, 10)
        self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value), self.tick)
        self.get_logger().info('Plan B custom planner ready: OpenCV/V2X/scan/odom -> /v2x/raw_path')

    def on_odom(self, msg: Odometry):
        self.odom = msg

    def on_scan(self, msg: LaserScan):
        self.scan = msg

    def on_lane_path(self, msg: Path):
        self.lane_path = msg
        self.lane_stamp = self.get_clock().now()

    def on_signal(self, msg: String):
        raw = msg.data.strip()
        try:
            data = json.loads(raw)
            self.signal_phase = str(data.get('current_phase', 'UNKNOWN')).upper()
        except json.JSONDecodeError:
            self.signal_phase = raw.upper()

    def lane_is_fresh(self) -> bool:
        if self.lane_path is None or self.lane_stamp is None:
            return False
        age = (self.get_clock().now() - self.lane_stamp).nanoseconds / 1e9
        return age <= float(self.get_parameter('lane_timeout_sec').value)

    def scan_detour_y(self) -> float:
        if self.scan is None:
            return 0.0
        scan = self.scan
        front_dist = float(self.get_parameter('obstacle_front_distance_m').value)
        front_width = float(self.get_parameter('obstacle_front_width_m').value)
        left_count = 0
        right_count = 0
        for i, r in enumerate(scan.ranges):
            if not math.isfinite(r) or r < scan.range_min or r > min(scan.range_max, front_dist):
                continue
            a = scan.angle_min + i * scan.angle_increment
            x = r * math.cos(a)
            y = r * math.sin(a)
            if x <= 0.0 or abs(y) > front_width:
                continue
            if y >= 0.0:
                left_count += 1
            else:
                right_count += 1
        if left_count + right_count == 0:
            return 0.0
        detour = float(self.get_parameter('detour_lateral_m').value)
        # If more obstacle points on left, detour right; otherwise detour left.
        return -detour if left_count >= right_count else detour

    def local_to_odom(self, lx: float, ly: float, ox: float, oy: float, yaw: float):
        wx = ox + math.cos(yaw) * lx - math.sin(yaw) * ly
        wy = oy + math.sin(yaw) * lx + math.cos(yaw) * ly
        return wx, wy

    def make_pose(self, x: float, y: float, yaw: float, frame_id: str) -> PoseStamped:
        pose = PoseStamped()
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.header.frame_id = frame_id
        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        pose.pose.position.z = 0.0
        pose.pose.orientation = quaternion_from_yaw(yaw)
        return pose

    def tick(self):
        if self.odom is None:
            return
        frame_id = str(self.get_parameter('output_frame_id').value)
        pose = self.odom.pose.pose
        ox = pose.position.x
        oy = pose.position.y
        oyaw = yaw_from_quaternion(pose.orientation)

        out = Path()
        out.header.stamp = self.get_clock().now().to_msg()
        out.header.frame_id = frame_id

        stop_for_light = bool(self.get_parameter('stop_on_red_yellow').value) and self.signal_phase in ('RED', 'YELLOW')
        if stop_for_light:
            # Publish a tiny hold path. The fallback node/mux also stops, but this keeps
            # the planner behavior explainable in plots/RViz.
            for _ in range(3):
                out.poses.append(self.make_pose(ox, oy, oyaw, frame_id))
            self.pub.publish(out)
            return

        n = max(4, int(self.get_parameter('path_points').value))
        length = float(self.get_parameter('path_length_m').value)
        detour_y = self.scan_detour_y()

        if self.lane_is_fresh() and self.lane_path.poses:
            # Lane path is in base_link by default: transform local lane points into odom.
            for p in self.lane_path.poses[:n]:
                lx = p.pose.position.x
                ly = p.pose.position.y + detour_y * 0.35
                wx, wy = self.local_to_odom(lx, ly, ox, oy, oyaw)
                # approximate heading along robot yaw; smoother will clean this up
                out.poses.append(self.make_pose(wx, wy, oyaw, frame_id))
        else:
            for i in range(n):
                t = i / float(n - 1)
                lx = t * length
                # Smooth obstacle detour: zero at start/end, max in middle.
                ly = detour_y * math.sin(math.pi * t)
                wx, wy = self.local_to_odom(lx, ly, ox, oy, oyaw)
                local_heading = math.atan2(detour_y * math.pi / length * math.cos(math.pi * t), 1.0) if abs(detour_y) > 1e-3 else 0.0
                out.poses.append(self.make_pose(wx, wy, oyaw + local_heading, frame_id))

        self.pub.publish(out)


def main(args=None):
    rclpy.init(args=args)
    node = CustomPathPlannerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
