#!/usr/bin/env python3
"""Emergency vehicle V2X requester connected to the Nav2/Gazebo simulator.

Old qcar-master version listened to /vehicle/pose. This integrated version uses
/odom from v2x_nav2_sim, so it follows the actual simulated robot pose.
"""

import json
import math

import rclpy
from nav_msgs.msg import Odometry
from rclpy.node import Node
from std_msgs.msg import String


REQUEST_DISTANCE_THRESHOLD = 12.0
TIMEOUT_SECONDS = 5.0
VEHICLE_ID = 'qcar_emergency_01'

# Matched to the small v2x_lab_world map instead of the older qcar world.
INTERSECTIONS = {
    'intersection_1': (-1.0, -4.0),
    'intersection_2': (3.0, 0.0),
}


class VehicleNode(Node):
    def __init__(self):
        super().__init__('vehicle_node')
        self.declare_parameter('odom_topic', '/odom')
        self.declare_parameter('urgency_level', 2)
        self.declare_parameter('vehicle_id', VEHICLE_ID)

        self.vehicle_id = str(self.get_parameter('vehicle_id').value)
        self.urgency_level = int(self.get_parameter('urgency_level').value)

        self.request_pub = self.create_publisher(String, '/v2x/priority_request', 10)
        self.create_subscription(String, '/v2x/priority_grant', self.grant_callback, 10)
        self.create_subscription(String, '/v2x/signal_status', self.signal_callback, 10)
        self.create_subscription(Odometry, self.get_parameter('odom_topic').value, self.odom_callback, 10)

        self.current_xy = None
        self.pending_requests = {}
        self.granted_intersections = set()
        self.speed_limit = 1.0
        self.create_timer(0.5, self.check_intersections)

        self.get_logger().info(
            f'[VehicleNode] ready | vehicle_id={self.vehicle_id} | urgency={self.urgency_level} | odom={self.get_parameter("odom_topic").value}'
        )

    def odom_callback(self, msg: Odometry):
        self.current_xy = (msg.pose.pose.position.x, msg.pose.pose.position.y)

    def check_intersections(self):
        if self.current_xy is None:
            return
        vx, vy = self.current_xy
        now = self.get_clock().now().nanoseconds / 1e9
        for intersection_id, (ix, iy) in INTERSECTIONS.items():
            dist = math.hypot(vx - ix, vy - iy)
            if intersection_id in self.granted_intersections:
                continue
            if intersection_id in self.pending_requests:
                if now - self.pending_requests[intersection_id] > TIMEOUT_SECONDS:
                    self.speed_limit = 0.3
                    self.get_logger().warn(f'[VehicleNode] timeout for {intersection_id}; slowing request cadence')
                    self.pending_requests.pop(intersection_id, None)
                continue
            if dist <= REQUEST_DISTANCE_THRESHOLD:
                eta = dist / max(self.speed_limit * 1.0, 0.1)
                self.send_priority_request(intersection_id, dist, eta)

    def send_priority_request(self, intersection_id: str, distance: float, eta: float):
        payload = {
            'vehicle_id': self.vehicle_id,
            'urgency_level': self.urgency_level,
            'distance_to_intersection': round(distance, 2),
            'estimated_arrival_time': round(eta, 2),
            'intersection_id': intersection_id,
        }
        msg = String()
        msg.data = json.dumps(payload)
        self.request_pub.publish(msg)
        self.pending_requests[intersection_id] = self.get_clock().now().nanoseconds / 1e9
        self.get_logger().info(
            f'[VehicleNode] request -> {intersection_id} | urgency={self.urgency_level} | dist={distance:.1f}m | ETA={eta:.1f}s'
        )

    def grant_callback(self, msg: String):
        try:
            data = json.loads(msg.data)
        except json.JSONDecodeError:
            self.get_logger().warn(f'[VehicleNode] ignored malformed grant: {msg.data!r}')
            return
        if data.get('vehicle_id') != self.vehicle_id:
            return
        intersection_id = data.get('intersection_id', 'unknown')
        if data.get('granted'):
            self.granted_intersections.add(intersection_id)
            self.pending_requests.pop(intersection_id, None)
            self.speed_limit = 1.0
            self.get_logger().info(f'[VehicleNode] grant received from {intersection_id}: {data.get("reason", "")}')
        else:
            self.speed_limit = 0.3
            self.get_logger().warn(f'[VehicleNode] grant denied at {intersection_id}: {data.get("reason", "")}')

    def signal_callback(self, msg: String):
        try:
            data = json.loads(msg.data)
        except json.JSONDecodeError:
            return
        self.get_logger().debug(
            f'[VehicleNode] signal {data.get("intersection_id")} -> {data.get("current_phase")} ({data.get("time_remaining")}s)'
        )


def main(args=None):
    rclpy.init(args=args)
    node = VehicleNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
