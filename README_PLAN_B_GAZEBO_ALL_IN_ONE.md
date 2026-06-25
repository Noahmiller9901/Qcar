# Plan B + Gazebo all-in-one workspace

This zip contains both:

1. The original `v2x_nav2_sim` Gazebo package from `v2x_nav2_jazzy_smac_gazebo`.
2. The Plan-B Nav2 replacement stack using QCar2, OpenCV perception, V2X traffic-light data, custom path planning, polynomial smoothing, MPPI, and the priority mux.

## Build

```bash
cd planb_ws_qcar2_gazebo
colcon build --symlink-install
source install/setup.bash
```

## Best full-GUI Plan B command

This starts Gazebo GUI with a QCar2 world and runs the custom Nav2 replacement stack:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_full_gazebo.launch.py
```

Choose one of the three QCar2 test worlds:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_full_gazebo.launch.py world:=qcar2_simple_grid_world.sdf
ros2 launch v2x_custom_stack plan_b_qcar2_full_gazebo.launch.py world:=qcar2_traffic_light_grid_world.sdf
ros2 launch v2x_custom_stack plan_b_qcar2_full_gazebo.launch.py world:=qcar2_eight_shape_road_world.sdf
```

The expected main ROS topics are:

```text
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
/v2x/opencv/lane_centerline_path
/v2x/raw_path
/v2x/smoothed_path
/mppi/cmd_vel
/qcar/cmd_vel
```

## If Gazebo is already running

Use the attach-only launch:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py spawn_qcar:=true world_name:=empty
```

If the QCar2 is already spawned:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py spawn_qcar:=false
```

## Original Gazebo package + Plan B stack

If the original `v2x_nav2_sim` Gazebo world starts correctly but Nav2 itself fails, run:

```bash
ros2 launch v2x_custom_stack plan_b_original_gazebo_full.launch.py
```

This uses the original topics:

```text
/odom
/scan
/cmd_vel
```

It does not launch Nav2. It only uses the original Gazebo simulation with the custom Plan-B stack.

## Original Nav2/Gazebo package still included

The original package is still available:

```bash
ros2 launch v2x_nav2_sim gazebo_sim.launch.py
ros2 launch v2x_nav2_sim full_nav2_gazebo.launch.py
```

Use those only if you want to continue Nav2 debugging.

## Notes

- `QCar2_original.urdf` is preserved exactly as uploaded.
- `QCar2_planb.urdf` fixes package mesh paths for ROS package lookup.
- `qcar2_planb/model.sdf` is the Gazebo-running companion model because the uploaded URDF does not include active Gazebo drive/lidar/camera/odom plugins.
- The placeholder `qcar_planb` model is still present as backup, but the preferred demo path is QCar2.

Quick sanity checks:

```bash
ros2 topic list | sort
ros2 topic echo /qcar/odom --once
ros2 topic echo /qcar/scan --once
ros2 topic echo /qcar/cmd_vel
```

Manual movement test:

```bash
ros2 topic pub /qcar/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}"
```
