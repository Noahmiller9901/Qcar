#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare('v2x_nav2_sim'), 'launch', 'gazebo_sim.launch.py'])
        ])
    )

    custom_stack = TimerAction(
        period=4.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource([
                    PathJoinSubstitution([FindPackageShare('v2x_custom_stack'), 'launch', 'plan_b_custom_stack.launch.py'])
                ])
            )
        ]
    )

    return LaunchDescription([gazebo, custom_stack])
