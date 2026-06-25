from launch import LaunchDescription
from launch.actions import GroupAction, IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node, SetRemap
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    nav_pkg = FindPackageShare('v2x_nav2_sim')
    nav2_bringup = FindPackageShare('nav2_bringup')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([nav_pkg, 'launch', 'gazebo_sim.launch.py'])
        ])
    )

    # Start Nav2 using the unmodified v2x_nav2_sim map/config, but remap its
    # controller output away from /cmd_vel so the priority mux owns /cmd_vel.
    nav2 = TimerAction(
        period=5.0,
        actions=[
            GroupAction([
                SetRemap(src='/cmd_vel', dst='/nav2/cmd_vel'),
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource([
                        PathJoinSubstitution([nav2_bringup, 'launch', 'bringup_launch.py'])
                    ]),
                    launch_arguments={
                        'use_sim_time': 'true',
                        'map': PathJoinSubstitution([nav_pkg, 'maps', 'v2x_lab_map.yaml']),
                        'params_file': PathJoinSubstitution([nav_pkg, 'config', 'nav2_smac_params.yaml']),
                        'autostart': 'true',
                    }.items(),
                ),
            ])
        ],
    )

    mppi = TimerAction(
        period=7.0,
        actions=[
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
            )
        ],
    )


    opencv_perception = TimerAction(
        period=7.0,
        actions=[
            Node(
                package='v2x_opencv_perception',
                executable='lane_detection_node',
                name='lane_detection_node',
                output='screen',
                parameters=[{
                    'camera_topic': '/qcar/camera/image_raw',
                    'lane_pixel_topic': '/v2x/opencv/lane_pixels',
                    'debug_mask_topic': '/v2x/opencv/lane_mask',
                    'publish_debug_mask': False,
                }],
            ),
            Node(
                package='v2x_opencv_perception',
                executable='lane_path_adapter_node',
                name='lane_path_adapter_node',
                output='screen',
                parameters=[{
                    'lane_pixel_topic': '/v2x/opencv/lane_pixels',
                    'lane_path_topic': '/v2x/opencv/lane_centerline_path',
                    'lane_status_topic': '/v2x/opencv/lane_status',
                    'frame_id': 'base_link',
                }],
            ),
        ],
    )

    mux_and_safety = TimerAction(
        period=7.0,
        actions=[
            Node(package='emergency_priority', executable='priority_mux_node', name='priority_mux_node', output='screen'),
            Node(package='emergency_priority', executable='v2x_fallback_node', name='v2x_fallback_node', output='screen'),
        ],
    )

    v2x = TimerAction(
        period=8.0,
        actions=[
            Node(package='v2x_emergency', executable='traffic_light_node', name='traffic_light_1', output='screen', arguments=['intersection_1']),
            Node(package='v2x_emergency', executable='traffic_light_node', name='traffic_light_2', output='screen', arguments=['intersection_2']),
            Node(package='v2x_emergency', executable='v2x_controller', name='v2x_controller', output='screen'),
            Node(package='v2x_emergency', executable='vehicle_node', name='vehicle_node', output='screen', parameters=[{'odom_topic': '/odom'}]),
        ],
    )

    return LaunchDescription([gazebo, nav2, opencv_perception, mppi, mux_and_safety, v2x])
