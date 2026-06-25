#!/usr/bin/env python3
"""Start one of the Plan-B worlds that already contains qcar_planb.

Do NOT use this if Gazebo is already running. Use spawn_qcar_planb.launch.py and
plan_b_attach_to_running_gazebo.launch.py instead.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, SetEnvironmentVariable
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    world = LaunchConfiguration('world')
    world_file = PathJoinSubstitution([FindPackageShare('v2x_custom_stack'), 'worlds', world])
    model_path = PathJoinSubstitution([FindPackageShare('v2x_custom_stack'), 'models'])
    return LaunchDescription([
        DeclareLaunchArgument('world', default_value='simple_grid_world.sdf'),
        SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', model_path),
        ExecuteProcess(cmd=['gz', 'sim', '-r', world_file], output='screen'),
    ])
