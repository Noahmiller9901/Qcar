from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg_share = FindPackageShare('v2x_nav2_sim')
    world = PathJoinSubstitution([pkg_share, 'worlds', 'v2x_lab_world.sdf'])
    robot_sdf = PathJoinSubstitution([pkg_share, 'models', 'qcar_simple', 'model.sdf'])
    bridge_config = PathJoinSubstitution([pkg_share, 'config', 'ros_gz_bridge.yaml'])

    gz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare('ros_gz_sim'), 'launch', 'gz_sim.launch.py'])
        ]),
        launch_arguments={'gz_args': ['-r ', world]}.items()
    )

    spawn_robot = TimerAction(
        period=2.0,
        actions=[
            Node(
                package='ros_gz_sim',
                executable='create',
                arguments=[
                    '-name', 'qcar_simple',
                    '-file', robot_sdf,
                    '-x', '-7.0',
                    '-y', '-4.0',
                    '-z', '0.15',
                    '-Y', '0.0',
                ],
                output='screen'
            )
        ]
    )

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': bridge_config}],
        output='screen'
    )

    return LaunchDescription([
        SetEnvironmentVariable(
            name='GZ_SIM_RESOURCE_PATH',
            value=PathJoinSubstitution([pkg_share, 'models'])
        ),
        gz_launch,
        spawn_robot,
        bridge,
    ])
