#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    camera_topic = LaunchConfiguration('camera_topic')
    use_opencv = LaunchConfiguration('use_opencv')
    use_traffic_light = LaunchConfiguration('use_traffic_light')

    return LaunchDescription([
        DeclareLaunchArgument('camera_topic', default_value='/qcar/camera/image_raw'),
        DeclareLaunchArgument('use_opencv', default_value='true'),
        DeclareLaunchArgument('use_traffic_light', default_value='true'),

        # OpenCV perception only. No velocity commands from vision.
        Node(
            package='v2x_opencv_perception',
            executable='lane_detection_node',
            name='lane_detection_node',
            parameters=[{'camera_topic': camera_topic}],
            condition=None,
            output='screen',
        ),
        Node(
            package='v2x_opencv_perception',
            executable='lane_path_adapter_node',
            name='lane_path_adapter_node',
            output='screen',
        ),

        # V2X traffic light simulation/control data.
        Node(
            package='v2x_emergency',
            executable='traffic_light_node',
            name='traffic_light_intersection_1',
            arguments=['intersection_1'],
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='traffic_light_gate_node',
            name='traffic_light_gate_node',
            output='screen',
        ),

        # Plan B replacement for Nav2 costmap + planner + smoother.
        Node(
            package='v2x_custom_stack',
            executable='custom_costmap_node',
            name='custom_costmap_node',
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='custom_path_planner_node',
            name='custom_path_planner_node',
            output='screen',
        ),
        Node(
            package='v2x_custom_stack',
            executable='polynomial_smoother_node',
            name='polynomial_smoother_node',
            output='screen',
        ),

        # Reuse MPPI follower, but feed it Plan B's smoothed path instead of Nav2 /plan.
        Node(
            package='v2x_mppi_lane_avoidance',
            executable='mppi_path_follower',
            name='mppi_path_follower',
            parameters=[{
                'plan_topic': '/v2x/smoothed_path',
                'cmd_topic': '/mppi/cmd_vel',
                'stop_without_plan': True,
            }],
            output='screen',
        ),

        # Existing priority mux owns final /cmd_vel.
        Node(
            package='emergency_priority',
            executable='priority_mux_node',
            name='priority_mux_node',
            output='screen',
        ),
    ])
