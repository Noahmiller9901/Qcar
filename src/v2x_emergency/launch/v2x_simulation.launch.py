from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([

        # ── V2X Controller (central monitor) ────────────────
        Node(
            package="v2x_emergency",
            executable="v2x_controller",
            name="v2x_controller",
            output="screen",
        ),

        # ── Traffic Light 1 ──────────────────────────────────
        Node(
            package="v2x_emergency",
            executable="traffic_light_node",
            name="traffic_light_1",
            output="screen",
            arguments=["intersection_1"],
        ),

        # ── Traffic Light 2 ──────────────────────────────────
        Node(
            package="v2x_emergency",
            executable="traffic_light_node",
            name="traffic_light_2",
            output="screen",
            arguments=["intersection_2"],
        ),

        # ── Emergency Vehicle ────────────────────────────────
        Node(
            package='v2x_emergency',
            executable='vehicle_node',
            name='vehicle_node',
            output='screen',
            parameters=[{'odom_topic': '/odom'}],
        ),
    ])
