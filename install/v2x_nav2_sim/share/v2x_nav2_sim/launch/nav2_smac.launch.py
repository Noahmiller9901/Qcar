from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg_share = FindPackageShare('v2x_nav2_sim')
    nav2_bringup_share = FindPackageShare('nav2_bringup')

    params_file = PathJoinSubstitution([pkg_share, 'config', 'nav2_smac_params.yaml'])
    map_file = PathJoinSubstitution([pkg_share, 'maps', 'v2x_lab_map.yaml'])

    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([nav2_bringup_share, 'launch', 'bringup_launch.py'])
        ]),
        launch_arguments={
            'use_sim_time': 'true',
            'map': map_file,
            'params_file': params_file,
            'autostart': 'true',
        }.items()
    )

    return LaunchDescription([nav2])
