from glob import glob
from setuptools import setup

package_name = 'v2x_custom_stack'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', glob('launch/*.launch.py')),
        ('share/' + package_name + '/config', glob('config/*.yaml')),
        ('share/' + package_name + '/worlds', glob('worlds/*.sdf')),
        ('share/' + package_name + '/maps', glob('maps/*')),
        ('share/' + package_name + '/models/qcar_planb', glob('models/qcar_planb/*')),
    ],
    install_requires=['setuptools', 'numpy'],
    zip_safe=True,
    maintainer='V2X Team',
    maintainer_email='student@example.com',
    description='Plan B custom V2X/OpenCV planner stack for QCar/Gazebo demos.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'custom_costmap_node = v2x_custom_stack.custom_costmap_node:main',
            'custom_path_planner_node = v2x_custom_stack.custom_path_planner_node:main',
            'polynomial_smoother_node = v2x_custom_stack.polynomial_smoother_node:main',
            'traffic_light_gate_node = v2x_custom_stack.traffic_light_gate_node:main',
        ],
    },
)
