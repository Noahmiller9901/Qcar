from setuptools import setup, find_packages
from glob import glob
import os

package_name = 'v2x_mppi_lane_avoidance'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools', 'numpy'],
    zip_safe=True,
    maintainer='Prathamesh Sathe',
    maintainer_email='prathamesh@example.com',
    description='ROS 2 wrapper for polynomial MPPI lane/path tracking and obstacle avoidance.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'mppi_path_follower = v2x_mppi_lane_avoidance.mppi_path_follower_node:main',
        ],
    },
)
