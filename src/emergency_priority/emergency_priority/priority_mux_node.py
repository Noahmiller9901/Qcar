#!/usr/bin/env python3
"""Configurable priority mux for V2X / MPPI / optional Nav2 commands.

This version is Plan-B friendly: all topic names can be changed from launch
arguments, because Gazebo/QCar examples often disagree on /cmd_vel vs
/QCar/cmd_vel vs /model/<name>/cmd_vel.
"""

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node


class PriorityMuxNode(Node):
    def __init__(self):
        super().__init__('priority_mux_node')

        self.declare_parameter('output_topic', '/cmd_vel')
        self.declare_parameter('v2x_fallback_topic', '/v2x/fallback_cmd_vel')
        self.declare_parameter('mppi_cmd_topic', '/mppi/cmd_vel')
        self.declare_parameter('nav2_cmd_topic', '/nav2/cmd_vel')
        self.declare_parameter('source_timeout_sec', 0.5)
        self.declare_parameter('publish_rate_hz', 20.0)
        self.declare_parameter('enable_nav2_source', False)

        timeout = float(self.get_parameter('source_timeout_sec').value)
        self.sources = [
            ('v2x_fallback', str(self.get_parameter('v2x_fallback_topic').value), 100, timeout),
            ('mppi_path_follower', str(self.get_parameter('mppi_cmd_topic').value), 50, timeout),
        ]
        if bool(self.get_parameter('enable_nav2_source').value):
            self.sources.append(('nav2_controller', str(self.get_parameter('nav2_cmd_topic').value), 10, timeout))

        self.sources = sorted(self.sources, key=lambda s: s[2], reverse=True)
        self.last_msg = {name: None for name, *_ in self.sources}
        self.last_time = {name: None for name, *_ in self.sources}

        for name, topic, _prio, _timeout in self.sources:
            self.create_subscription(Twist, topic, lambda msg, n=name: self.on_cmd(msg, n), 10)

        output_topic = str(self.get_parameter('output_topic').value)
        self.pub = self.create_publisher(Twist, output_topic, 10)
        self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value), self.tick)
        self.get_logger().info(
            f'Priority mux ready. Output -> {output_topic}. Sources: ' +
            ', '.join(f'{name}:{topic}(p={prio})' for name, topic, prio, _ in self.sources)
        )

    def on_cmd(self, msg: Twist, name: str):
        self.last_msg[name] = msg
        self.last_time[name] = self.get_clock().now()

    def is_active(self, name: str, timeout: float) -> bool:
        stamp = self.last_time[name]
        if stamp is None:
            return False
        age = (self.get_clock().now() - stamp).nanoseconds / 1e9
        return age <= timeout

    def tick(self):
        for name, _topic, prio, timeout in self.sources:
            if self.is_active(name, timeout):
                self.pub.publish(self.last_msg[name])
                self.get_logger().info(f'cmd_vel <- {name} (priority {prio})', throttle_duration_sec=1.0)
                return
        self.pub.publish(Twist())
        self.get_logger().info('cmd_vel <- STOP: no active command source', throttle_duration_sec=1.0)


def main(args=None):
    rclpy.init(args=args)
    node = PriorityMuxNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
