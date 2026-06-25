#!/usr/bin/env python3
"""Bridge QCar2 Plan-B Gazebo topics into ROS 2."""

from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    bridge_config = PathJoinSubstitution([
        FindPackageShare('qcar2_description'),
        'config',
        'qcar2_ros_gz_bridge.yaml',
    ])
    return LaunchDescription([
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            name='qcar2_bridge',
            parameters=[{'config_file': bridge_config}],
            output='screen',
        ),
    ])
