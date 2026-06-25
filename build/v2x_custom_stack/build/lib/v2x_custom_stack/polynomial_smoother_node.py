#!/usr/bin/env python3
"""Polynomial path smoother for the Plan B stack.

Consumes /v2x/raw_path and publishes /v2x/smoothed_path. This replaces Nav2's
smoother layer when Nav2 is not usable.
"""

import math
from typing import Optional

import numpy as np
import rclpy
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
from rclpy.node import Node

from .common import quaternion_from_yaw


class PolynomialSmootherNode(Node):
    def __init__(self):
        super().__init__('polynomial_smoother_node')
        self.declare_parameter('raw_path_topic', '/v2x/raw_path')
        self.declare_parameter('smoothed_path_topic', '/v2x/smoothed_path')
        self.declare_parameter('polynomial_order', 3)
        self.declare_parameter('output_points', 60)
        self.declare_parameter('publish_rate_hz', 10.0)
        self.latest_path: Optional[Path] = None
        self.create_subscription(Path, self.get_parameter('raw_path_topic').value, self.on_path, 10)
        self.pub = self.create_publisher(Path, self.get_parameter('smoothed_path_topic').value, 10)
        self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value), self.tick)
        self.get_logger().info('Plan B polynomial smoother ready: /v2x/raw_path -> /v2x/smoothed_path')

    def on_path(self, msg: Path):
        self.latest_path = msg

    def tick(self):
        if self.latest_path is None or len(self.latest_path.poses) < 3:
            return
        pts = self.latest_path.poses
        xs = np.array([p.pose.position.x for p in pts], dtype=float)
        ys = np.array([p.pose.position.y for p in pts], dtype=float)
        # Parameterize by accumulated distance, so the smoother works for vertical/curved paths.
        s = np.zeros(len(xs), dtype=float)
        for i in range(1, len(xs)):
            s[i] = s[i - 1] + math.hypot(xs[i] - xs[i - 1], ys[i] - ys[i - 1])
        if s[-1] < 1e-3:
            self.pub.publish(self.latest_path)
            return
        order = min(int(self.get_parameter('polynomial_order').value), len(xs) - 1)
        cx = np.polyfit(s, xs, order)
        cy = np.polyfit(s, ys, order)
        dense_s = np.linspace(0.0, s[-1], max(4, int(self.get_parameter('output_points').value)))
        dense_x = np.polyval(cx, dense_s)
        dense_y = np.polyval(cy, dense_s)

        out = Path()
        out.header.stamp = self.get_clock().now().to_msg()
        out.header.frame_id = self.latest_path.header.frame_id
        for i in range(len(dense_s)):
            pose = PoseStamped()
            pose.header = out.header
            pose.pose.position.x = float(dense_x[i])
            pose.pose.position.y = float(dense_y[i])
            pose.pose.position.z = 0.0
            if i < len(dense_s) - 1:
                yaw = math.atan2(dense_y[i + 1] - dense_y[i], dense_x[i + 1] - dense_x[i])
            else:
                yaw = math.atan2(dense_y[i] - dense_y[i - 1], dense_x[i] - dense_x[i - 1])
            pose.pose.orientation = quaternion_from_yaw(yaw)
            out.poses.append(pose)
        self.pub.publish(out)


def main(args=None):
    rclpy.init(args=args)
    node = PolynomialSmootherNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
