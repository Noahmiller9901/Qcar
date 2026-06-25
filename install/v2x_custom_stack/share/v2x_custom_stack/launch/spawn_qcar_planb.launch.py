#!/usr/bin/env python3
"""Spawn the Plan-B QCar model into an already-running Gazebo world."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    world_name = LaunchConfiguration('world_name')
    model_name = LaunchConfiguration('model_name')
    x = LaunchConfiguration('x')
    y = LaunchConfiguration('y')
    z = LaunchConfiguration('z')
    yaw = LaunchConfiguration('yaw')
    model_file = PathJoinSubstitution([
        FindPackageShare('v2x_custom_stack'),
        'models',
        'qcar_planb',
        'model.sdf',
    ])

    return LaunchDescription([
        DeclareLaunchArgument('world_name', default_value='empty'),
        DeclareLaunchArgument('model_name', default_value='qcar'),
        DeclareLaunchArgument('x', default_value='0.0'),
        DeclareLaunchArgument('y', default_value='0.0'),
        DeclareLaunchArgument('z', default_value='0.12'),
        DeclareLaunchArgument('yaw', default_value='0.0'),
        ExecuteProcess(
            cmd=[
                'ros2', 'run', 'ros_gz_sim', 'create',
                '-world', world_name,
                '-file', model_file,
                '-name', model_name,
                '-x', x,
                '-y', y,
                '-z', z,
                '-Y', yaw,
            ],
            output='screen',
        ),
    ])
