# Integration changelog v2

## Added

- Added `v2x_opencv_perception` package from the QCar OpenCV lane detection code.
- Added lane path/status adapter for future Nav2 costmap or custom planner consumption.
- Added OpenCV perception nodes to the main integrated launch.

## Changed

- Renamed `v2x_mpc_lane_avoidance` to `v2x_mppi_lane_avoidance`.
- Renamed controller output from `/mpc/cmd_vel` to `/mppi/cmd_vel`.
- Updated priority mux to read `/mppi/cmd_vel`.
- Updated V2X vehicle node to use `/odom` instead of `/vehicle/pose`.
- Updated V2X demo launch files so they do not start the old lane controller or fake pose publisher.
- Converted the old stand-in lane controller into a debug-only publisher disconnected from the mux.

## Preserved

- `v2x_nav2_sim` was not modified.

## Removed/neutralized conflicts

- OpenCV no longer directly controls the robot.
- V2X communication nodes do not directly control the robot.
- Nav2 no longer publishes directly to final `/cmd_vel`; it is remapped to `/nav2/cmd_vel`.
- Final `/cmd_vel` is owned by the priority mux only.
