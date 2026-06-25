#!/usr/bin/env python3
"""Attach Plan B stack to an already-running Gazebo/QCar simulation.

Use this when Gazebo is already open. It launches only ROS 2 planning/control
nodes and lets you pass whatever topic names your current sim uses.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    odom_topic = LaunchConfiguration('odom_topic')
    scan_topic = LaunchConfiguration('scan_topic')
    camera_topic = LaunchConfiguration('camera_topic')
    cmd_vel_output = LaunchConfiguration('cmd_vel_output')
    signal_topic = LaunchConfiguration('signal_topic')
    mppi_cmd_topic = LaunchConfiguration('mppi_cmd_topic')
    lane_path_topic = LaunchConfiguration('lane_path_topic')
    raw_path_topic = LaunchConfiguration('raw_path_topic')
    smoothed_path_topic = LaunchConfiguration('smoothed_path_topic')
    local_costmap_topic = LaunchConfiguration('local_costmap_topic')
    use_sim_time = LaunchConfiguration('use_sim_time')

    return LaunchDescription([
        DeclareLaunchArgument('odom_topic', default_value='/odom'),
        DeclareLaunchArgument('scan_topic', default_value='/scan'),
        DeclareLaunchArgument('camera_topic', default_value='/qcar/camera/image_raw'),
        DeclareLaunchArgument('cmd_vel_output', default_value='/cmd_vel'),
        DeclareLaunchArgument('signal_topic', default_value='/v2x/signal_status'),
        DeclareLaunchArgument('mppi_cmd_topic', default_value='/mppi/cmd_vel'),
        DeclareLaunchArgument('lane_path_topic', default_value='/v2x/opencv/lane_centerline_path'),
        DeclareLaunchArgument('raw_path_topic', default_value='/v2x/raw_path'),
        DeclareLaunchArgument('smoothed_path_topic', default_value='/v2x/smoothed_path'),
        DeclareLaunchArgument('local_costmap_topic', default_value='/v2x/local_costmap'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),

        Node(
            package='v2x_opencv_perception',
            executable='lane_detection_node',
            name='lane_detection_node',
            parameters=[{'camera_topic': camera_topic, 'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='v2x_opencv_perception',
            executable='lane_path_adapter_node',
            name='lane_path_adapter_node',
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='v2x_emergency',
            executable='traffic_light_node',
            name='traffic_light_intersection_1',
            arguments=['intersection_1'],
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='traffic_light_gate_node',
            name='traffic_light_gate_node',
            parameters=[{'signal_topic': signal_topic, 'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='custom_costmap_node',
            name='custom_costmap_node',
            parameters=[{
                'odom_topic': odom_topic,
                'scan_topic': scan_topic,
                'signal_topic': signal_topic,
                'costmap_topic': local_costmap_topic,
                'use_sim_time': use_sim_time,
            }],
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='custom_path_planner_node',
            name='custom_path_planner_node',
            parameters=[{
                'odom_topic': odom_topic,
                'scan_topic': scan_topic,
                'lane_path_topic': lane_path_topic,
                'signal_topic': signal_topic,
                'raw_path_topic': raw_path_topic,
                'use_sim_time': use_sim_time,
            }],
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='polynomial_smoother_node',
            name='polynomial_smoother_node',
            parameters=[{
                'raw_path_topic': raw_path_topic,
                'smoothed_path_topic': smoothed_path_topic,
                'use_sim_time': use_sim_time,
            }],
            output='screen',
        ),
        Node(
            package='v2x_mppi_lane_avoidance',
            executable='mppi_path_follower',
            name='mppi_path_follower',
            parameters=[{
                'plan_topic': smoothed_path_topic,
                'odom_topic': odom_topic,
                'scan_topic': scan_topic,
                'cmd_topic': mppi_cmd_topic,
                'stop_without_plan': True,
                'use_sim_time': use_sim_time,
            }],
            output='screen',
        ),
        Node(
            package='emergency_priority',
            executable='priority_mux_node',
            name='priority_mux_node',
            parameters=[{
                'output_topic': cmd_vel_output,
                'mppi_cmd_topic': mppi_cmd_topic,
                'v2x_fallback_topic': '/v2x/fallback_cmd_vel',
                'enable_nav2_source': False,
                'use_sim_time': use_sim_time,
            }],
            output='screen',
        ),
    ])
