from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'emergency_priority'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
            glob('launch/*.launch.py')),
        (os.path.join('share', package_name, 'config'),
            glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='hassan',
    maintainer_email='hassan@todo.todo',
    description='V2X fallback safety node for the emergency vehicle project.',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'v2x_fallback_node = emergency_priority.v2x_fallback_node:main',
            'priority_mux_node = emergency_priority.priority_mux_node:main',
            'standin_lane_controller = emergency_priority.standin_lane_controller:main',
        ],
    },
)
