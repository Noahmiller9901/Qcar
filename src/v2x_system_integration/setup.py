from setuptools import setup
from glob import glob
import os

package_name = 'v2x_system_integration'

setup(
    name=package_name,
    version='0.1.0',
    packages=[],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Prathamesh Sathe',
    maintainer_email='prathamesh@example.com',
    description='V2X system integration launch package.',
    license='MIT',
)
