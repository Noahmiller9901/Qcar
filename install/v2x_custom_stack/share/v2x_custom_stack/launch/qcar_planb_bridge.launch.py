#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    bridge_config = PathJoinSubstitution([
        FindPackageShare('v2x_custom_stack'),
        'config',
        'qcar_planb_ros_gz_bridge.yaml',
    ])
    return LaunchDescription([
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            name='qcar_planb_bridge',
            parameters=[{'config_file': bridge_config}],
            output='screen',
        ),
    ])
