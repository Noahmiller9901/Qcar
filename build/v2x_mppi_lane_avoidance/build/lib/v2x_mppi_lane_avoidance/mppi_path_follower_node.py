#!/usr/bin/env python3
"""
ROS 2 adapter for the starter MPPI + polynomial lane/path tracking code.

Contract with v2x_nav2_sim, without changing that package:
  subscribes: /plan        nav_msgs/Path          global path from Nav2
              /odom        nav_msgs/Odometry      Gazebo odometry
              /scan        sensor_msgs/LaserScan  optional obstacle layer
  publishes:  /mppi/cmd_vel geometry_msgs/Twist    velocity command for mux

The polynomial is fitted in the robot's local frame. This keeps the original
starter math usable even when the global map path is not aligned with world X.
"""

import math
from typing import List, Optional, Tuple

import numpy as np
import rclpy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry, Path
from rclpy.node import Node
from sensor_msgs.msg import LaserScan

from .curve_generator import fit_trajectory_polynomial
from .mppi_core import MPPIConfig, MPPIController, StaticObstacle


def yaw_from_quaternion(q) -> float:
    siny_cosp = 2.0 * (q.w * q.z + q.x * q.y)
    cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z)
    return math.atan2(siny_cosp, cosy_cosp)


def clamp(value: float, low: float, high: float) -> float:
    return max(low, min(high, value))


class MPPIPathFollower(Node):
    def __init__(self):
        super().__init__('mppi_path_follower')

        self.declare_parameter('plan_topic', '/plan')
        self.declare_parameter('odom_topic', '/odom')
        self.declare_parameter('scan_topic', '/scan')
        self.declare_parameter('cmd_topic', '/mppi/cmd_vel')
        self.declare_parameter('publish_rate_hz', 10.0)
        self.declare_parameter('lookahead_points', 35)
        self.declare_parameter('min_forward_points', 2)
        self.declare_parameter('target_speed', 0.8)
        self.declare_parameter('max_linear_speed', 1.2)
        self.declare_parameter('stop_without_plan', True)
        self.declare_parameter('use_scan_obstacles', True)

        self.cfg = MPPIConfig()
        self.cfg.target_speed = float(self.get_parameter('target_speed').value)
        self.cfg.max_speed = float(self.get_parameter('max_linear_speed').value)
        self.controller = MPPIController(self.cfg)

        self.latest_path: Optional[Path] = None
        self.latest_odom: Optional[Odometry] = None
        self.latest_scan: Optional[LaserScan] = None

        self.create_subscription(Path, self.get_parameter('plan_topic').value, self.on_path, 10)
        self.create_subscription(Odometry, self.get_parameter('odom_topic').value, self.on_odom, 20)
        self.create_subscription(LaserScan, self.get_parameter('scan_topic').value, self.on_scan, 10)
        self.cmd_pub = self.create_publisher(Twist, self.get_parameter('cmd_topic').value, 10)

        rate = float(self.get_parameter('publish_rate_hz').value)
        self.create_timer(1.0 / rate, self.tick)

        self.get_logger().info(
            'MPPI path follower ready: /plan + /odom + /scan -> /mppi/cmd_vel. '
            'Use priority_mux_node to forward this to /cmd_vel.'
        )

    def on_path(self, msg: Path):
        self.latest_path = msg

    def on_odom(self, msg: Odometry):
        self.latest_odom = msg

    def on_scan(self, msg: LaserScan):
        self.latest_scan = msg

    def robot_state(self) -> Optional[Tuple[float, float, float, float]]:
        if self.latest_odom is None:
            return None
        pose = self.latest_odom.pose.pose
        twist = self.latest_odom.twist.twist
        x = pose.position.x
        y = pose.position.y
        yaw = yaw_from_quaternion(pose.orientation)
        speed = math.hypot(twist.linear.x, twist.linear.y)
        return x, y, yaw, speed

    def path_points_in_robot_frame(self, x: float, y: float, yaw: float) -> Tuple[np.ndarray, np.ndarray]:
        if self.latest_path is None or not self.latest_path.poses:
            return np.array([]), np.array([])

        cos_yaw = math.cos(yaw)
        sin_yaw = math.sin(yaw)
        local_points: List[Tuple[float, float]] = []
        for stamped_pose in self.latest_path.poses:
            px = stamped_pose.pose.position.x - x
            py = stamped_pose.pose.position.y - y
            # world -> robot local frame
            lx = cos_yaw * px + sin_yaw * py
            ly = -sin_yaw * px + cos_yaw * py
            if lx > 0.05:
                local_points.append((lx, ly))

        local_points.sort(key=lambda p: p[0])
        local_points = local_points[: int(self.get_parameter('lookahead_points').value)]
        if not local_points:
            return np.array([]), np.array([])

        xs = np.array([p[0] for p in local_points], dtype=float)
        ys = np.array([p[1] for p in local_points], dtype=float)
        return xs, ys

    def scan_obstacles(self) -> List[StaticObstacle]:
        if not bool(self.get_parameter('use_scan_obstacles').value) or self.latest_scan is None:
            return []

        obstacles: List[StaticObstacle] = []
        scan = self.latest_scan
        angle = scan.angle_min
        # Downsample to avoid hundreds of obstacle objects per control tick.
        step = max(1, int(len(scan.ranges) / 60))
        for i in range(0, len(scan.ranges), step):
            r = scan.ranges[i]
            a = scan.angle_min + i * scan.angle_increment
            if not math.isfinite(r):
                continue
            if r < scan.range_min or r > min(scan.range_max, 3.0):
                continue
            ox = r * math.cos(a)
            oy = r * math.sin(a)
            # Only model objects in front-ish of the robot.
            if ox > 0.1 and abs(oy) < 1.75:
                obstacles.append(StaticObstacle(ox, oy, 0.25))
        return obstacles[:20]

    def publish_stop(self):
        self.cmd_pub.publish(Twist())

    def tick(self):
        state = self.robot_state()
        if state is None:
            self.publish_stop()
            return

        x, y, yaw, speed = state
        xs, ys = self.path_points_in_robot_frame(x, y, yaw)
        min_pts = int(self.get_parameter('min_forward_points').value)
        if len(xs) < min_pts:
            if bool(self.get_parameter('stop_without_plan').value):
                self.publish_stop()
            return

        coeffs = fit_trajectory_polynomial(xs, ys, order=2)
        obstacles = self.scan_obstacles()

        accel, steer, _rx, _ry = self.controller.solve(
            0.0, 0.0, 0.0, speed, obstacles, coeffs
        )

        next_speed = clamp(speed + accel * self.cfg.dt, 0.0, self.cfg.max_speed)
        angular_z = 0.0
        if abs(steer) > 1e-4:
            angular_z = next_speed * math.tan(steer) / self.cfg.wheelbase

        cmd = Twist()
        cmd.linear.x = float(clamp(next_speed, 0.0, self.cfg.max_speed))
        cmd.angular.z = float(clamp(angular_z, -2.0, 2.0))
        self.cmd_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = MPPIPathFollower()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
