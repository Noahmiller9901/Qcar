from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='v2x_mppi_lane_avoidance',
            executable='mppi_path_follower',
            name='mppi_path_follower',
            output='screen',
            parameters=[{
                'plan_topic': '/plan',
                'odom_topic': '/odom',
                'scan_topic': '/scan',
                'cmd_topic': '/mppi/cmd_vel',
                'target_speed': 0.8,
                'max_linear_speed': 1.2,
            }],
        ),
    ])
