# Plan B with Gazebo already running

Use this version when Gazebo is already open and your topic names do not match the default `/odom`, `/scan`, `/cmd_vel`.

## 1. Check actual ROS topics

```bash
ros2 topic list | sort
ros2 topic echo /clock --once
ros2 topic info /odom
ros2 topic info /scan
ros2 topic info /cmd_vel
```

If your QCar topics are namespaced, use those names in the launch arguments. Common examples:

```text
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
/qcar/cmd_vel
```

or older QCar style:

```text
/QCar/odom
/QCar/scan
/QCar/camera/image_raw
/QCar/cmd_vel
```

## 2. Attach Plan B to the running sim

For the included Plan-B QCar model:

```bash
ros2 launch v2x_custom_stack qcar_planb_bridge.launch.py
ros2 launch v2x_custom_stack plan_b_attach_to_running_gazebo.launch.py \
  odom_topic:=/qcar/odom \
  scan_topic:=/qcar/scan \
  camera_topic:=/qcar/camera/image_raw \
  cmd_vel_output:=/qcar/cmd_vel
```

For the old un-namespaced Nav2/Gazebo style:

```bash
ros2 launch v2x_custom_stack plan_b_attach_to_running_gazebo.launch.py \
  odom_topic:=/odom \
  scan_topic:=/scan \
  camera_topic:=/qcar/camera/image_raw \
  cmd_vel_output:=/cmd_vel
```

## 3. Spawn the Plan-B QCar into an already-running Gazebo world

Only do this if your current Gazebo world does not already have a robot. Replace `world_name` with the name from the Gazebo window or from `gz topic -l`.

```bash
ros2 launch v2x_custom_stack spawn_qcar_planb.launch.py world_name:=empty model_name:=qcar x:=0 y:=0 yaw:=0
```

The included QCar publishes Gazebo topics that are bridged to ROS as:

```text
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
/qcar/cmd_vel
```

## 4. Start one of the included worlds instead of using an existing Gazebo

Do not use this if Gazebo is already running.

```bash
ros2 launch v2x_custom_stack plan_b_qcar_world.launch.py world:=simple_grid_world.sdf
ros2 launch v2x_custom_stack qcar_planb_bridge.launch.py
ros2 launch v2x_custom_stack plan_b_attach_to_running_gazebo.launch.py odom_topic:=/qcar/odom scan_topic:=/qcar/scan camera_topic:=/qcar/camera/image_raw cmd_vel_output:=/qcar/cmd_vel
```

Available worlds:

```text
simple_grid_world.sdf
traffic_light_grid_world.sdf
eight_shape_road_world.sdf
```

Available map YAMLs:

```text
simple_grid_map.yaml
traffic_light_grid_map.yaml
eight_shape_road_map.yaml
```

## Important

`qcar-master.zip` did not include an official Quanser QCar Gazebo/URDF model. It had OpenCV lane keeping and V2X code, plus a simple box ambulance world. This package therefore includes a QCar-style Gazebo model with camera, lidar, odom, and cmd_vel so the demo can run. If you later get the official QCar model, keep this architecture and swap only the model/topic arguments.
