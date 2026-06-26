Yup. Tomorrow’s mission should be **execution only**, not new feature hell.

Your 3 tasks are exactly right, but order matters:

## Tomorrow priority order

### 1. Get it running on university PC first

Before touching physics, do the dependency check:

```bash
source /opt/ros/jazzy/setup.bash
ros2 --version
gz sim --versions
ros2 pkg list | grep ros_gz_bridge
ros2 pkg list | grep cv_bridge
colcon --version
python3 -c "import cv2, numpy; print('opencv/numpy ok')"
```

If this passes, continue there. If not, go back to The Construct and record there.

---

## Task 1: Fix physics / tumbling

Start with the safest test:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.02}, angular: {z: 0.0}}" -r 10
```

If it tumbles even at `0.02`, the model physics/collision is bad.

Most likely fixes:

```text
- Raise/lower QCar spawn Z slightly
- Increase mass/inertia stability
- Simplify collision geometry
- Reduce friction weirdness
- Reduce max speed from MPPI
```

First easy fix should be **reduce command speed**, because it is fastest.

We can patch MPPI to be demo-safe:

```text
target_speed: 0.05
max_linear_speed: 0.08
angular_z clamp smaller
```

For the demo, stable slow movement is better than chaotic fast movement.

---

## Task 2: Make sure maps load

Test maps one by one:

```bash
gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_simple_grid_world.sdf
```

Then:

```bash
gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_traffic_light_grid_world.sdf
```

Then:

```bash
gz sim -v 4 src/v2x_custom_stack/worlds/qcar2_eight_shape_road_world.sdf
```

Before each one:

```bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:$PWD/src/qcar2_description/models:$PWD/src/v2x_custom_stack/models
```

For each map, confirm:

```text
- world opens
- QCar appears
- camera/lidar load
- DiffDrive subscribes to /qcar/cmd_vel
```

If one map fails, don’t spend forever. Use the simple grid world for recording.

---

## Task 3: Record the presentable video

Record this exact story:

```text
1. Show Gazebo world + QCar visible.
2. Show ROS topics:
   /qcar/cmd_vel
   /qcar/scan
   /qcar/camera/image_raw
   /mppi/cmd_vel
   /v2x/signal_status
3. Show RED signal:
   fallback STOP active.
4. Show GREEN signal:
   MPPI and /qcar/cmd_vel publish.
5. Show slow visual movement if physics is stable.
6. Explain architecture.
```

Useful commands:

```bash
ros2 topic list | grep -E "qcar|v2x|mppi"
```

```bash
ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'RED'}" -r 2
```

```bash
ros2 topic pub /v2x/signal_status std_msgs/msg/String "{data: 'GREEN'}" -r 2
```

```bash
ros2 topic echo /mppi/cmd_vel --once
ros2 topic echo /qcar/cmd_vel --once
```

## Script for what to say

> This demo shows a custom Nav2 replacement stack for a QCar in Gazebo. The system combines OpenCV perception, V2X traffic-light communication, custom costmap and path planning, polynomial smoothing, MPPI control, and a priority mux. When the V2X signal is RED, the fallback stop command has highest priority and blocks motion. When the signal becomes GREEN, MPPI commands are allowed through the mux to `/qcar/cmd_vel`. The QCar model includes simulated camera, lidar, odometry, and Gazebo drive control.

That’s clean and defensible.

Tomorrow’s rule: **first get a stable recording, then improve.** Don’t wait for perfect physics before recording proof.
