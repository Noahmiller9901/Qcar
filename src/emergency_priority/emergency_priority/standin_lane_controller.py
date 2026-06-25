#!/usr/bin/env python3
"""Legacy/manual debug publisher.

The original stand-in lane controller could publish into the active command
chain. That conflicts with Nav2 -> polynomial -> MPPI -> priority mux, so this
node now publishes only to /debug/standin_cmd_vel and is not launched by the
integrated stack.
"""

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node


class StandinLaneController(Node):
    def __init__(self):
        super().__init__('standin_lane_controller')
        self.declare_parameter('cmd_topic', '/debug/standin_cmd_vel')
        self.declare_parameter('linear_speed', 0.0)
        self.declare_parameter('angular_speed', 0.0)
        self.pub = self.create_publisher(Twist, self.get_parameter('cmd_topic').value, 10)
        self.create_timer(0.1, self.tick)
        self.get_logger().warn(
            'Debug-only standin controller active. It is intentionally disconnected from /cmd_vel and the mux.'
        )

    def tick(self):
        msg = Twist()
        msg.linear.x = float(self.get_parameter('linear_speed').value)
        msg.angular.z = float(self.get_parameter('angular_speed').value)
        self.pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = StandinLaneController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
