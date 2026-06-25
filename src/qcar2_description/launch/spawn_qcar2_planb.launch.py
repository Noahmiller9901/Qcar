#!/usr/bin/env python3
"""Spawn QCar2 Plan-B SDF into an already-running Gazebo Sim world."""

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
        FindPackageShare('qcar2_description'),
        'models',
        'qcar2_planb',
        'model.sdf',
    ])

    return LaunchDescription([
        DeclareLaunchArgument('world_name', default_value='empty'),
        DeclareLaunchArgument('model_name', default_value='qcar2'),
        DeclareLaunchArgument('x', default_value='0.0'),
        DeclareLaunchArgument('y', default_value='0.0'),
        DeclareLaunchArgument('z', default_value='0.08'),
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
