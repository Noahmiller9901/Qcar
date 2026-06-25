#!/usr/bin/env python3
"""Safety fallback for traffic-light state.

Accepts both the older plain states ("RED") and the newer JSON payloads from
v2x_emergency/traffic_light_node.py ({"current_phase":"RED", ...}).
"""

import json

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node
from std_msgs.msg import String


LIGHT_STATE_TOPIC = '/v2x/signal_status'
FALLBACK_CMD_TOPIC = '/v2x/fallback_cmd_vel'
STALE_DATA_TIMEOUT_SEC = 2.0
CONTROL_RATE_HZ = 10.0


class V2XFallbackNode(Node):
    def __init__(self):
        super().__init__('v2x_fallback_node')
        self.last_light_state = None
        self.last_msg_time = None
        self.create_subscription(String, LIGHT_STATE_TOPIC, self.on_light_state, 10)
        self.cmd_pub = self.create_publisher(Twist, FALLBACK_CMD_TOPIC, 10)
        self.create_timer(1.0 / CONTROL_RATE_HZ, self.control_loop)
        self.get_logger().info(f'V2X fallback ready: {LIGHT_STATE_TOPIC} -> {FALLBACK_CMD_TOPIC}')

    def on_light_state(self, msg: String):
        raw = msg.data.strip()
        try:
            data = json.loads(raw)
            state = data.get('current_phase', raw)
        except json.JSONDecodeError:
            state = raw
        self.last_light_state = str(state).strip().upper()
        self.last_msg_time = self.get_clock().now()

    def is_data_stale(self) -> bool:
        if self.last_msg_time is None:
            return True
        age_sec = (self.get_clock().now() - self.last_msg_time).nanoseconds / 1e9
        return age_sec > STALE_DATA_TIMEOUT_SEC

    def control_loop(self):
        stop = False
        reason = ''
        if self.is_data_stale():
            stop = True
            reason = 'no recent V2X data'
        elif self.last_light_state in ('RED', 'YELLOW'):
            stop = True
            reason = self.last_light_state.lower()
        elif self.last_light_state == 'GREEN':
            stop = False
            reason = 'green'
        else:
            stop = True
            reason = f'unknown state {self.last_light_state!r}'

        if stop:
            self.cmd_pub.publish(Twist())
        self.get_logger().info(f'{"STOP" if stop else "GO"} | {reason}', throttle_duration_sec=1.0)


def main(args=None):
    rclpy.init(args=args)
    node = V2XFallbackNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
