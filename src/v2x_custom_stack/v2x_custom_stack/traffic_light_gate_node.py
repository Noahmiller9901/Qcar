#!/usr/bin/env python3
"""Optional traffic-light gate for Plan B demos.

This node publishes /v2x/fallback_cmd_vel only when RED/YELLOW/unknown signal
requires a stop. It is compatible with the existing priority mux.
"""

import json

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node
from std_msgs.msg import String


class TrafficLightGateNode(Node):
    def __init__(self):
        super().__init__('traffic_light_gate_node')
        self.declare_parameter('signal_topic', '/v2x/signal_status')
        self.declare_parameter('fallback_cmd_topic', '/v2x/fallback_cmd_vel')
        self.declare_parameter('stale_timeout_sec', 2.0)
        self.declare_parameter('publish_rate_hz', 10.0)
        self.phase = 'UNKNOWN'
        self.last_msg_time = None
        self.create_subscription(String, self.get_parameter('signal_topic').value, self.on_signal, 10)
        self.pub = self.create_publisher(Twist, self.get_parameter('fallback_cmd_topic').value, 10)
        self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value), self.tick)
        self.get_logger().info('Traffic-light gate ready: RED/YELLOW/unknown -> /v2x/fallback_cmd_vel STOP')

    def on_signal(self, msg: String):
        raw = msg.data.strip()
        try:
            data = json.loads(raw)
            self.phase = str(data.get('current_phase', 'UNKNOWN')).upper()
        except json.JSONDecodeError:
            self.phase = raw.upper()
        self.last_msg_time = self.get_clock().now()

    def stale(self):
        if self.last_msg_time is None:
            return True
        return (self.get_clock().now() - self.last_msg_time).nanoseconds / 1e9 > float(self.get_parameter('stale_timeout_sec').value)

    def tick(self):
        if self.stale() or self.phase in ('RED', 'YELLOW', 'UNKNOWN'):
            self.pub.publish(Twist())
            self.get_logger().info(f'Fallback STOP active | signal={self.phase}', throttle_duration_sec=1.0)
        else:
            self.get_logger().info(f'Fallback clear | signal={self.phase}', throttle_duration_sec=1.0)


def main(args=None):
    rclpy.init(args=args)
    node = TrafficLightGateNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
