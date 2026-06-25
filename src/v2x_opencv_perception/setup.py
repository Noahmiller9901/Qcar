from setuptools import setup, find_packages
from glob import glob
import os

package_name = 'v2x_opencv_perception'

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
    description='OpenCV lane perception for Nav2/cost-planning integration. No direct velocity control.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'lane_detection_node = v2x_opencv_perception.lane_detection_node:main',
            'lane_path_adapter_node = v2x_opencv_perception.lane_path_adapter_node:main',
        ],
    },
)
