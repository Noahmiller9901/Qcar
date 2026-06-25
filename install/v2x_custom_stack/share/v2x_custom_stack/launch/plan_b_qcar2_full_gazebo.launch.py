#!/usr/bin/env python3
"""Start Gazebo GUI with a QCar2 Plan-B world and run the Nav2 replacement stack.

Use this when you want the complete demo in one command:
  Gazebo world + QCar2 SDF + ROS-Gazebo bridge + OpenCV/V2X/custom planner/MPPI/mux.

This does NOT launch Nav2. It is the Plan-B replacement stack.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    world = LaunchConfiguration('world')
    use_sim_time = LaunchConfiguration('use_sim_time')

    custom_share = FindPackageShare('v2x_custom_stack')
    qcar2_share = FindPackageShare('qcar2_description')

    world_file = PathJoinSubstitution([custom_share, 'worlds', world])
    qcar2_models = PathJoinSubstitution([qcar2_share, 'models'])
    custom_models = PathJoinSubstitution([custom_share, 'models'])

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare('ros_gz_sim'), 'launch', 'gz_sim.launch.py'])
        ]),
        launch_arguments={'gz_args': ['-r ', world_file]}.items(),
    )

    qcar2_bridge = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([qcar2_share, 'launch', 'qcar2_bridge.launch.py'])
        ])
    )

    qcar2_state_publisher = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([qcar2_share, 'launch', 'qcar2_state_publisher.launch.py'])
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items(),
    )

    plan_b_stack = TimerAction(
        period=3.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource([
                    PathJoinSubstitution([custom_share, 'launch', 'plan_b_attach_to_running_gazebo.launch.py'])
                ]),
                launch_arguments={
                    'odom_topic': '/qcar/odom',
                    'scan_topic': '/qcar/scan',
                    'camera_topic': '/qcar/camera/image_raw',
                    'cmd_vel_output': '/qcar/cmd_vel',
                    'use_sim_time': use_sim_time,
                }.items(),
            )
        ],
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world',
            default_value='qcar2_simple_grid_world.sdf',
            description='World file from v2x_custom_stack/worlds. Options: qcar2_simple_grid_world.sdf, qcar2_traffic_light_grid_world.sdf, qcar2_eight_shape_road_world.sdf',
        ),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', [qcar2_models, ':', custom_models]),
        gazebo,
        qcar2_bridge,
        qcar2_state_publisher,
        plan_b_stack,
    ])
