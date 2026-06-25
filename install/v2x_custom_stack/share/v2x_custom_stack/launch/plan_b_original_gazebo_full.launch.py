#!/usr/bin/env python3
"""Start the original v2x_nav2_sim Gazebo world, but run Plan B instead of Nav2.

This is useful if the original Gazebo package runs but Nav2 does not. It starts:
  v2x_nav2_sim Gazebo world + qcar_simple + original bridge + custom Plan-B stack.
Topics are the original un-namespaced ones: /odom, /scan, /cmd_vel.
"""

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    gazebo_original = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare('v2x_nav2_sim'), 'launch', 'gazebo_sim.launch.py'])
        ])
    )

    plan_b_stack = TimerAction(
        period=4.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource([
                    PathJoinSubstitution([FindPackageShare('v2x_custom_stack'), 'launch', 'plan_b_attach_to_running_gazebo.launch.py'])
                ]),
                launch_arguments={
                    'odom_topic': '/odom',
                    'scan_topic': '/scan',
                    'camera_topic': '/qcar/camera/image_raw',
                    'cmd_vel_output': '/cmd_vel',
                    'use_sim_time': 'true',
                }.items(),
            )
        ],
    )

    return LaunchDescription([gazebo_original, plan_b_stack])
