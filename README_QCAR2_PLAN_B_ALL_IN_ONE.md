# V2X Plan B Custom Stack with QCar2 URDF

This workspace is the all-in-one Plan B fallback for the V2X/QCar simulation when Nav2 is not stable enough.

It includes:

- `qcar2_description` — package built from the uploaded `QCar2.urdf`.
- `v2x_custom_stack` — Nav2 replacement planner layer.
- `v2x_opencv_perception` — OpenCV lane perception only, no direct `/cmd_vel` control.
- `v2x_mppi_lane_avoidance` — MPPI follower.
- `v2x_emergency` and `emergency_priority` — V2X traffic light / fallback / command mux.
- Three demo maps/worlds: simple grid, traffic-light grid, and eight-shape road.
- The original `v2x_nav2_sim` package is still present but not required by the Plan B launch.

## Main architecture

```text
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
/v2x/signal_status
        ↓
OpenCV + V2X + custom cost/path planner
        ↓
/v2x/raw_path
        ↓
polynomial smoother
        ↓
/v2x/smoothed_path
        ↓
MPPI follower
        ↓
/mppi/cmd_vel
        ↓
priority mux
        ↓
/qcar/cmd_vel
```

## Build

```bash
cd planb_ws_qcar2
colcon build --symlink-install
source install/setup.bash
```

## Use when Gazebo is already running

Start Gazebo first. Then run:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py \
  world_name:=empty \
  spawn_qcar:=true
```

If the QCar2 is already spawned, do not spawn it again:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py \
  spawn_qcar:=false
```

## If your Gazebo world name is not `empty`

Check Gazebo worlds/topics and pass the actual world name:

```bash
gz topic -l | grep world
```

Example:

```bash
ros2 launch v2x_custom_stack plan_b_qcar2_nav2_replacement.launch.py \
  world_name:=traffic_light_grid_world \
  spawn_qcar:=true
```

## Expected ROS topics

After launch, these should exist:

```bash
ros2 topic list | grep qcar
```

Expected:

```text
/qcar/cmd_vel
/qcar/odom
/qcar/scan
/qcar/camera/image_raw
```

Planner outputs:

```text
/v2x/local_costmap
/v2x/raw_path
/v2x/smoothed_path
/mppi/cmd_vel
```

## QCar2 URDF notes

The uploaded `QCar2.urdf` is kept here:

```text
src/qcar2_description/urdf/QCar2_original.urdf
```

A package-path patched copy is here:

```text
src/qcar2_description/urdf/QCar2_planb.urdf
```

For Gazebo movement/sensors, the workspace uses this SDF companion model:

```text
src/qcar2_description/models/qcar2_planb/model.sdf
```

Reason: the uploaded URDF defines the QCar2 physical structure, but it does not include working ROS 2/Gazebo Sim drive, lidar, camera, or odometry plugins. The SDF companion adds those demo-ready interfaces.

## Three demo environments

Worlds:

```text
src/v2x_custom_stack/worlds/simple_grid_world.sdf
src/v2x_custom_stack/worlds/traffic_light_grid_world.sdf
src/v2x_custom_stack/worlds/eight_shape_road_world.sdf
```

Maps:

```text
src/v2x_custom_stack/maps/simple_grid_map.yaml
src/v2x_custom_stack/maps/traffic_light_grid_map.yaml
src/v2x_custom_stack/maps/eight_shape_road_map.yaml
```

## Important

This is demo-grade Plan B. It replaces the Nav2 planner/control path with a custom stack so the simulation can still run for the progress meeting. It is not a full production-quality Nav2 replacement yet.
