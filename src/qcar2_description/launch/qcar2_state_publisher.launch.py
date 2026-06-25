#!/usr/bin/env python3
"""Publish QCar2 robot_description from the uploaded URDF for RViz/debugging."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')
    urdf_path = PathJoinSubstitution([
        FindPackageShare('qcar2_description'), 'urdf', 'QCar2_planb.urdf'
    ])

    robot_description = {'robot_description': Command(['cat ', urdf_path])}

    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='qcar2_robot_state_publisher',
            parameters=[robot_description, {'use_sim_time': use_sim_time}],
            output='screen',
        ),
    ])
