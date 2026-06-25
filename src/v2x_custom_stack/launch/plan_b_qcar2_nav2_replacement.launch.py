#!/usr/bin/env python3
"""Complete Plan-B launch for an already-running Gazebo Sim instance.

This is the one-button fallback when Nav2 is not usable:
  QCar2 spawn/bridge + OpenCV perception + V2X + custom planner + polynomial smoother + MPPI + mux.
It does NOT start Gazebo. Start Gazebo first, then run this launch.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    spawn_qcar = LaunchConfiguration('spawn_qcar')
    world_name = LaunchConfiguration('world_name')
    model_name = LaunchConfiguration('model_name')
    x = LaunchConfiguration('x')
    y = LaunchConfiguration('y')
    z = LaunchConfiguration('z')
    yaw = LaunchConfiguration('yaw')
    use_sim_time = LaunchConfiguration('use_sim_time')

    qcar2_spawn_launch = PathJoinSubstitution([
        FindPackageShare('qcar2_description'), 'launch', 'spawn_qcar2_planb.launch.py'
    ])
    qcar2_bridge_launch = PathJoinSubstitution([
        FindPackageShare('qcar2_description'), 'launch', 'qcar2_bridge.launch.py'
    ])
    attach_launch = PathJoinSubstitution([
        FindPackageShare('v2x_custom_stack'), 'launch', 'plan_b_attach_to_running_gazebo.launch.py'
    ])

    return LaunchDescription([
        DeclareLaunchArgument('spawn_qcar', default_value='true', description='Spawn the QCar2 model into an already-running Gazebo world.'),
        DeclareLaunchArgument('world_name', default_value='empty', description='Gazebo world name. Use the world name shown by gz topic -l / ros_gz.'),
        DeclareLaunchArgument('model_name', default_value='qcar2'),
        DeclareLaunchArgument('x', default_value='0.0'),
        DeclareLaunchArgument('y', default_value='0.0'),
        DeclareLaunchArgument('z', default_value='0.08'),
        DeclareLaunchArgument('yaw', default_value='0.0'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(qcar2_spawn_launch),
            condition=IfCondition(spawn_qcar),
            launch_arguments={
                'world_name': world_name,
                'model_name': model_name,
                'x': x,
                'y': y,
                'z': z,
                'yaw': yaw,
            }.items(),
        ),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(qcar2_bridge_launch),
        ),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(attach_launch),
            launch_arguments={
                'odom_topic': '/qcar/odom',
                'scan_topic': '/qcar/scan',
                'camera_topic': '/qcar/camera/image_raw',
                'cmd_vel_output': '/qcar/cmd_vel',
                'use_sim_time': use_sim_time,
            }.items(),
        ),
    ])
