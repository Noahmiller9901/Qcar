from setuptools import find_packages
from setuptools import setup

setup(
    name='v2x_emergency',
    version='0.1.0',
    packages=find_packages(
        include=('v2x_emergency', 'v2x_emergency.*')),
)
