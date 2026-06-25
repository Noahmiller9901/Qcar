from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='v2x_opencv_perception',
            executable='lane_detection_node',
            name='lane_detection_node',
            output='screen',
            parameters=[{
                # v2x_nav2_sim currently has lidar/odom/cmd_vel but no camera.
                # Keep this remappable for the final QCar/camera model.
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
                'camera_width_px': 640.0,
                'meters_per_pixel': 0.003,
                'frame_id': 'base_link',
            }],
        ),
    ])
