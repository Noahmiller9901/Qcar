
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([

        Node(
            package='emergency_priority',
            executable='standin_lane_controller',
            name='standin_lane_controller',
            output='screen',
        ),

        Node(
            package='emergency_priority',
            executable='v2x_fallback_node',
            name='v2x_fallback_node',
            output='screen',
        ),

        Node(
            package='emergency_priority',
            executable='priority_mux_node',
            name='priority_mux_node',
            output='screen',
        ),
    ])
