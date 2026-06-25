from setuptools import setup
from glob import glob
import os

package_name = 'v2x_nav2_sim'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        (os.path.join('share', package_name, 'maps'), glob('maps/*')),
        (os.path.join('share', package_name, 'worlds'), glob('worlds/*')),
        (os.path.join('share', package_name, 'models/qcar_simple'), glob('models/qcar_simple/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Prathamesh Sathe',
    maintainer_email='prathamesh@example.com',
    description='V2X Nav2 Smac + Gazebo starter package for ROS 2 Jazzy.',
    license='MIT',
)
