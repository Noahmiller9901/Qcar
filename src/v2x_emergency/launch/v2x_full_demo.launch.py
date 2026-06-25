"""Integrated-safe V2X demo launcher.

The old qcar-master launcher started lane_keeping_node and a fake /vehicle/pose
publisher. Those conflict with the agreed Nav2 -> polynomial -> MPPI -> mux
pipeline, so this launcher now starts only V2X communication nodes. Use
v2x_system_integration/integrated_v2x_nav2_mppi.launch.py for the full stack.
"""

from launch import LaunchDescription
from launch.actions import TimerAction
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        TimerAction(period=0.0, actions=[
            Node(package='v2x_emergency', executable='traffic_light_node', name='traffic_light_1', output='screen', arguments=['intersection_1']),
            Node(package='v2x_emergency', executable='traffic_light_node', name='traffic_light_2', output='screen', arguments=['intersection_2']),
            Node(package='v2x_emergency', executable='v2x_controller', name='v2x_controller', output='screen'),
        ]),
        TimerAction(period=1.0, actions=[
            Node(
                package='v2x_emergency',
                executable='vehicle_node',
                name='vehicle_node',
                output='screen',
                parameters=[{'odom_topic': '/odom'}],
            )
        ]),
    ])
