#!/usr/bin/env python3
"""Lightweight local costmap for the Plan B stack.

This does NOT try to clone Nav2 costmaps. It only creates a demo-ready local
occupancy grid from /scan and V2X traffic-light state. OpenCV lane data is kept
as advisory path input for the planner, not as a velocity command.
"""

import json
import math
from typing import Optional

import rclpy
from nav_msgs.msg import OccupancyGrid, Odometry
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String

from .common import yaw_from_quaternion


class CustomCostmapNode(Node):
    def __init__(self):
        super().__init__('custom_costmap_node')
        self.declare_parameter('odom_topic', '/odom')
        self.declare_parameter('scan_topic', '/scan')
        self.declare_parameter('signal_topic', '/v2x/signal_status')
        self.declare_parameter('costmap_topic', '/v2x/local_costmap')
        self.declare_parameter('frame_id', 'odom')
        self.declare_parameter('width_m', 20.0)
        self.declare_parameter('height_m', 20.0)
        self.declare_parameter('resolution', 0.1)
        self.declare_parameter('scan_max_range_m', 8.0)
        self.declare_parameter('obstacle_inflation_cells', 2)
        self.declare_parameter('traffic_stop_x_m', 5.0)
        self.declare_parameter('traffic_stop_half_width_m', 2.0)
        self.declare_parameter('publish_rate_hz', 5.0)

        self.latest_odom: Optional[Odometry] = None
        self.latest_scan: Optional[LaserScan] = None
        self.signal_phase = 'UNKNOWN'

        self.create_subscription(Odometry, self.get_parameter('odom_topic').value, self.on_odom, 20)
        self.create_subscription(LaserScan, self.get_parameter('scan_topic').value, self.on_scan, 10)
        self.create_subscription(String, self.get_parameter('signal_topic').value, self.on_signal, 10)
        self.pub = self.create_publisher(OccupancyGrid, self.get_parameter('costmap_topic').value, 10)
        self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value), self.publish_costmap)
        self.get_logger().info('Plan B custom costmap ready: /scan + V2X signal -> /v2x/local_costmap')

    def on_odom(self, msg: Odometry):
        self.latest_odom = msg

    def on_scan(self, msg: LaserScan):
        self.latest_scan = msg

    def on_signal(self, msg: String):
        raw = msg.data.strip()
        try:
            data = json.loads(raw)
            self.signal_phase = str(data.get('current_phase', 'UNKNOWN')).upper()
        except json.JSONDecodeError:
            self.signal_phase = raw.upper()

    def publish_costmap(self):
        width_m = float(self.get_parameter('width_m').value)
        height_m = float(self.get_parameter('height_m').value)
        res = float(self.get_parameter('resolution').value)
        w = int(width_m / res)
        h = int(height_m / res)
        data = [0] * (w * h)

        cx_world = 0.0
        cy_world = 0.0
        yaw = 0.0
        if self.latest_odom is not None:
            pose = self.latest_odom.pose.pose
            cx_world = pose.position.x
            cy_world = pose.position.y
            yaw = yaw_from_quaternion(pose.orientation)

        origin_x = cx_world - width_m / 2.0
        origin_y = cy_world - height_m / 2.0

        def set_cell_world(wx: float, wy: float, value: int = 100, inflation: int = 0):
            mx = int((wx - origin_x) / res)
            my = int((wy - origin_y) / res)
            for dx in range(-inflation, inflation + 1):
                for dy in range(-inflation, inflation + 1):
                    ix = mx + dx
                    iy = my + dy
                    if 0 <= ix < w and 0 <= iy < h:
                        data[iy * w + ix] = max(data[iy * w + ix], value)

        if self.latest_scan is not None:
            scan = self.latest_scan
            scan_max = float(self.get_parameter('scan_max_range_m').value)
            inflation = int(self.get_parameter('obstacle_inflation_cells').value)
            for i, r in enumerate(scan.ranges):
                if not math.isfinite(r) or r < scan.range_min or r > min(scan.range_max, scan_max):
                    continue
                a = scan.angle_min + i * scan.angle_increment
                # laser/base_link to odom frame. Assumes scan frame is aligned with base_link for demo.
                lx = r * math.cos(a)
                ly = r * math.sin(a)
                wx = cx_world + math.cos(yaw) * lx - math.sin(yaw) * ly
                wy = cy_world + math.sin(yaw) * lx + math.cos(yaw) * ly
                set_cell_world(wx, wy, 100, inflation)

        # Simple virtual stop wall for RED/YELLOW traffic light testing.
        if self.signal_phase in ('RED', 'YELLOW') and self.latest_odom is not None:
            stop_x = cx_world + float(self.get_parameter('traffic_stop_x_m').value) * math.cos(yaw)
            half_w = float(self.get_parameter('traffic_stop_half_width_m').value)
            for k in range(-int(half_w / res), int(half_w / res) + 1):
                wx = stop_x - math.sin(yaw) * k * res
                wy = cy_world + float(self.get_parameter('traffic_stop_x_m').value) * math.sin(yaw) + math.cos(yaw) * k * res
                set_cell_world(wx, wy, 80, 1)

        grid = OccupancyGrid()
        grid.header.stamp = self.get_clock().now().to_msg()
        grid.header.frame_id = str(self.get_parameter('frame_id').value)
        grid.info.resolution = res
        grid.info.width = w
        grid.info.height = h
        grid.info.origin.position.x = origin_x
        grid.info.origin.position.y = origin_y
        grid.info.origin.orientation.w = 1.0
        grid.data = data
        self.pub.publish(grid)


def main(args=None):
    rclpy.init(args=args)
    node = CustomCostmapNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
