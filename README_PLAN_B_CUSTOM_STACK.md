# V2X Plan B Custom Planner Stack

This workspace keeps the existing `v2x_nav2_sim` package unchanged, but adds a Nav2-independent fallback stack for the progress demo.

## Architecture

```text
OpenCV lane perception + V2X traffic-light communication + /scan + /odom
        ↓
v2x_custom_stack/custom_costmap_node
v2x_custom_stack/custom_path_planner_node
        ↓
/v2x/raw_path
        ↓
v2x_custom_stack/polynomial_smoother_node
        ↓
/v2x/smoothed_path
        ↓
v2x_mppi_lane_avoidance/mppi_path_follower
        ↓
/mppi/cmd_vel
        ↓
emergency_priority/priority_mux_node
        ↓
/cmd_vel
```

## What this replaces

This bypasses Nav2 planner/controller lifecycle, costmap plugins, Hybrid A*, and Nav2 smoother. It does **not** bypass Gazebo, odom, scan, OpenCV, V2X, polynomial smoothing, MPPI, or the final mux.

## Main launch commands

Build:

```bash
cd planb_ws
colcon build --symlink-install
source install/setup.bash
```

Start only the Plan B stack after your simulator is already running:

```bash
ros2 launch v2x_custom_stack plan_b_custom_stack.launch.py
```

Start Gazebo using the unchanged simulator launch, then start Plan B automatically:

```bash
ros2 launch v2x_custom_stack plan_b_with_gazebo.launch.py
```

## Main topics

Inputs:

```text
/odom
/scan
/qcar/camera/image_raw
/v2x/opencv/lane_centerline_path
/v2x/signal_status
/v2x/priority_request
/v2x/priority_grant
```

Outputs:

```text
/v2x/local_costmap
/v2x/raw_path
/v2x/smoothed_path
/mppi/cmd_vel
/v2x/fallback_cmd_vel
/cmd_vel
```

## Demo maps/worlds included

The package includes placeholder demo assets:

```text
v2x_custom_stack/maps/simple_grid_map.yaml
v2x_custom_stack/maps/traffic_light_grid_map.yaml
v2x_custom_stack/maps/eight_shape_road_map.yaml

v2x_custom_stack/worlds/simple_grid_world.sdf
v2x_custom_stack/worlds/traffic_light_grid_world.sdf
v2x_custom_stack/worlds/eight_shape_road_world.sdf
```

The maps are for RViz/planning visualization. The worlds are simple Gazebo/Ignition SDF test scenes. They are intentionally lightweight so they can be edited quickly.

## Reality check

This is a demo-grade fallback, not a full industrial Nav2 replacement. It is meant to show modular integration and vehicle motion when Nav2 TF/costmap/plugin issues block progress.
