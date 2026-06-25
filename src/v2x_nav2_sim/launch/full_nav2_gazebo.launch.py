from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg_share = FindPackageShare('v2x_nav2_sim')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([pkg_share, 'launch', 'gazebo_sim.launch.py'])
        ])
    )

    # Delay Nav2 slightly so Gazebo, robot, scan, odom, and TF have time to appear.
    nav2 = TimerAction(
        period=5.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource([
                    PathJoinSubstitution([pkg_share, 'launch', 'nav2_smac.launch.py'])
                ])
            )
        ]
    )

    return LaunchDescription([gazebo, nav2])
