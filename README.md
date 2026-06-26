Absolutely. Save this as your **tomorrow command sheet**. Copy-paste only, no side quests.

---

# 0. First dependency check on university PC

Run this before cloning/building:

```bash
source /opt/ros/jazzy/setup.bash

ros2 --version
gz sim --versions
ros2 pkg list | grep ros_gz_bridge
ros2 pkg list | grep cv_bridge
colcon --version
python3 -c "import cv2, numpy; print('opencv/numpy ok')"
```

If all commands work, continue.

If `ros_gz_bridge`, `gz sim`, or `cv_bridge` is missing and you have no `sudo`, the university PC is not usable.

---

# 1. Clone repo

```bash
cd ~
git clone https://github.com/Noahmiller9901/Qcar.git
cd Qcar
rm -rf build install log
```

---

# 2. Patch snippet we changed

This is the `robot_description` YAML parsing fix.

Run this after cloning:

```bash
cd ~/Qcar

python3 - <<'PY'
from pathlib import Path

path = Path("src/qcar2_description/launch/qcar2_state_publisher.launch.py")
text = path.read_text()

# Add ParameterValue import
if "from launch_ros.parameter_descriptions import ParameterValue" not in text:
    text = text.replace(
        "from launch_ros.actions import Node\n",
        "from launch_ros.actions import Node\nfrom launch_ros.parameter_descriptions import ParameterValue\n"
    )

# Replace robot_description line
old = "    robot_description = {'robot_description': Command(['cat ', urdf_path])}"
new = """    robot_description = {
        'robot_description': ParameterValue(Command(['cat ', urdf_path]), value_type=str)
    }"""

if old in text:
    text = text.replace(old, new)
    path.write_text(text)
    print("Patched robot_description successfully.")
elif "ParameterValue(Command(['cat ', urdf_path]), value_type=str)" in text:
    print("Already patched.")
else:
    print("Could not find exact robot_description line. Inspect file manually.")
PY
```

The changed snippet should become this:

```python
from launch_ros.parameter_descriptions import ParameterValue
```

and:

```python
robot_description = {
    'robot_description': ParameterValue(Command(['cat ', urdf_path]), value_type=str)
}
```

Instead of:

```python
robot_description = {'robot_description': Command(['cat ', urdf_path])}
```

---

# 3. Build workspace

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash

colcon build --symlink-install \
  --cmake-args \
    -DPython3_EXECUTABLE=/usr/bin/python3 \
    -DPython_EXECUTABLE=/usr/bin/python3

source install/setup.bash
```

---

# 4. Common setup for every terminal

Run this in **every new terminal**:

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models
```

This is important. Without it, Gazebo may say:

```text
Unable to find uri[model://qcar2_planb]
```

---

# 5. Terminal 1: launch Gazebo simple map

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models

gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_simple_grid_world.sdf
```

Leave this terminal running.

Expected good signs:

```text
DiffDrive subscribing to twist messages on [/qcar/cmd_vel]
Camera images advertised on [/qcar/camera/image_raw]
Laser scans advertised on [/qcar/scan]
```

---

# 6. Terminal 2: launch custom stack

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models

ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py spawn_qcar:=false
```

Leave this terminal running.

Expected nodes:

```text
lane_detection_node
lane_path_adapter_node
traffic_light_node
traffic_light_gate_node
custom_costmap_node
custom_path_planner_node
polynomial_smoother_node
mppi_path_follower
priority_mux_node
```

---

# 7. Terminal 3: safety and demo commands

First, force RED so the car does not go crazy immediately:

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash

ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'RED'}" -r 2
```

Check important topics:

```bash
ros2 topic list | grep -E "qcar|v2x|mppi"
```

Check command path:

```bash
ros2 topic echo /mppi/cmd_vel --once
```

```bash
ros2 topic echo /qcar/cmd_vel --once
```

Switch to GREEN:

```bash
ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'GREEN'}" -r 2
```

Emergency stop / safety stop:

```bash
ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'RED'}" -r 2
```

Direct stop:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" -r 10
```

---

# 8. Manual slow movement test

Only do this when signal is RED or autonomous stack is stopped, so MPPI does not fight you.

Tiny movement:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.02}, angular: {z: 0.0}}" -r 10
```

Slightly faster:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.05}, angular: {z: 0.0}}" -r 10
```

Stop:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" -r 10
```

Do **not** start with `0.3`. That made the car act possessed.

---

# 9. Test all maps

Before each map, make sure no old Gazebo is running.

Kill old Gazebo:

```bash
pkill -f gz || true
pkill -f ruby || true
```

Simple grid:

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models

gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_simple_grid_world.sdf
```

Traffic light grid:

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models

gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_traffic_light_grid_world.sdf
```

Eight-shape road:

```bash
cd ~/Qcar
source /opt/ros/jazzy/setup.bash
source install/setup.bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models

gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_eight_shape_road_world.sdf
```

If one map fails, do not waste time. Use the simple grid world for recording.

---

# 10. Check Gazebo-native topics

Use this if ROS topics are not showing:

```bash
gz topic -l | grep qcar
```

Expected Gazebo topics:

```text
/qcar/cmd_vel
/qcar/scan
/qcar/camera/image_raw
```

Echo Gazebo command topic:

```bash
gz topic -e -t /qcar/cmd_vel
```

---

# 11. Check ROS topics

```bash
ros2 topic list | grep qcar
```

Expected ROS topics:

```text
/qcar/cmd_vel
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
```

Check rates:

```bash
ros2 topic hz /qcar/scan
ros2 topic hz /qcar/camera/image_raw
ros2 topic hz /qcar/odom
```

---

# 12. If the car tumbles

Immediately:

```bash
ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'RED'}" -r 2
```

Then:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" -r 10
```

If it still tumbles, kill the stack:

```bash
pkill -f mppi_path_follower || true
pkill -f priority_mux_node || true
```

Then test manual tiny speed only:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.02}, angular: {z: 0.0}}" -r 10
```

---

# 13. If Gazebo cannot find the model

Error:

```text
Unable to find uri[model://qcar2_planb]
```

Fix:

```bash
cd ~/Qcar
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models
```

Then retry Gazebo.

---

# 14. If `robot_description` YAML error appears

Error:

```text
Unable to parse the value of parameter robot_description as yaml
```

Run the patch again:

```bash
cd ~/Qcar

python3 - <<'PY'
from pathlib import Path

path = Path("src/qcar2_description/launch/qcar2_state_publisher.launch.py")
text = path.read_text()

if "from launch_ros.parameter_descriptions import ParameterValue" not in text:
    text = text.replace(
        "from launch_ros.actions import Node\n",
        "from launch_ros.actions import Node\nfrom launch_ros.parameter_descriptions import ParameterValue\n"
    )

old = "    robot_description = {'robot_description': Command(['cat ', urdf_path])}"
new = """    robot_description = {
        'robot_description': ParameterValue(Command(['cat ', urdf_path]), value_type=str)
    }"""

if old in text:
    text = text.replace(old, new)
    path.write_text(text)
    print("Patched robot_description successfully.")
elif "ParameterValue(Command(['cat ', urdf_path]), value_type=str)" in text:
    print("Already patched.")
else:
    print("Could not find exact robot_description line.")
PY
```

Then rebuild:

```bash
source /opt/ros/jazzy/setup.bash

colcon build --symlink-install --packages-select qcar2_description \
  --cmake-args \
    -DPython3_EXECUTABLE=/usr/bin/python3 \
    -DPython_EXECUTABLE=/usr/bin/python3

source install/setup.bash
```

---

# 15. Clean reset command

Use this if terminals get messy:

```bash
pkill -f gz || true
pkill -f ruby || true
pkill -f parameter_bridge || true
pkill -f mppi_path_follower || true
pkill -f priority_mux_node || true
pkill -f traffic_light || true
pkill -f lane_detection || true
pkill -f custom_costmap || true
pkill -f custom_path_planner || true
pkill -f polynomial_smoother || true
```

Then restart clean:

1. Terminal 1: Gazebo
2. Terminal 2: custom stack
3. Terminal 3: RED/GREEN commands

---

# 16. Recording script

Say this in the video:

```text
This demo shows a custom Nav2 replacement stack for a QCar in Gazebo. 
The system combines OpenCV lane perception, V2X traffic-light communication, 
a custom costmap, custom path planner, polynomial path smoothing, MPPI control, 
and a priority mux.

The Gazebo QCar model provides simulated camera, lidar, odometry, and drive control.
When the V2X signal is RED, the fallback stop command has highest priority and blocks motion.
When the signal becomes GREEN, the MPPI command is allowed through the priority mux to /qcar/cmd_vel.
This demonstrates the V2X safety override and the end-to-end command pipeline.
```

Demo sequence:

```text
1. Show Gazebo QCar visible.
2. Show terminal with qcar/v2x/mppi topics.
3. Publish RED.
4. Show fallback STOP active.
5. Publish GREEN.
6. Show /mppi/cmd_vel and /qcar/cmd_vel publishing.
7. Show slow visual movement if stable.
8. Switch back to RED as emergency stop.
```

---

# 17. Minimum success condition

Even if physics is cursed, you need to capture:

```text
QCar visible in Gazebo
/qcar/camera/image_raw exists
/qcar/scan exists
/v2x/signal_status works
RED activates fallback STOP
GREEN releases MPPI
/mppi/cmd_vel publishes
/qcar/cmd_vel publishes
```

That is enough to present the working architecture.
