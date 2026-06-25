# Plan B changelog

- Added `v2x_custom_stack` as a Nav2-independent fallback planner stack.
- Added `custom_costmap_node`: creates `/v2x/local_costmap` from `/scan` and traffic-light state.
- Added `custom_path_planner_node`: creates `/v2x/raw_path` from OpenCV lane path if available, otherwise a forward/detour local path.
- Added `polynomial_smoother_node`: converts `/v2x/raw_path` to `/v2x/smoothed_path`.
- Reused existing MPPI controller by remapping its `plan_topic` to `/v2x/smoothed_path`.
- Reused existing priority mux so only `/cmd_vel` drives Gazebo.
- Added `traffic_light_gate_node` compatible with `/v2x/signal_status` and `/v2x/fallback_cmd_vel`.
- Added simple grid, traffic-light grid, and eight-shape placeholder maps/worlds.
- Did not modify `v2x_nav2_sim`.

## v3 - QCar2 URDF + Nav2 replacement all-in-one

- Added `qcar2_description` package using the uploaded `QCar2.urdf`.
- Preserved original URDF as `QCar2_original.urdf`.
- Added package-path patched URDF as `QCar2_planb.urdf`.
- Added `qcar2_planb` Gazebo SDF companion model with:
  - `/qcar/cmd_vel`
  - `/qcar/odom`
  - `/qcar/scan`
  - `/qcar/camera/image_raw`
- Added QCar2 ROS-Gazebo bridge config.
- Added `plan_b_qcar2_nav2_replacement.launch.py` as the main all-in-one Plan B launch for already-running Gazebo.
- Kept old placeholder `qcar_planb` as backup only.

## v4 Gazebo all-in-one update

- Added QCar2-specific Gazebo worlds:
  - `qcar2_simple_grid_world.sdf`
  - `qcar2_traffic_light_grid_world.sdf`
  - `qcar2_eight_shape_road_world.sdf`
- Added `plan_b_qcar2_full_gazebo.launch.py` for one-command Gazebo GUI + QCar2 + Plan-B stack.
- Added `plan_b_original_gazebo_full.launch.py` to run the original `v2x_nav2_sim` Gazebo package with the Plan-B stack instead of Nav2.
- Kept original `v2x_nav2_sim` files included for continued debugging.
