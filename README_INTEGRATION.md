# V2X integrated workspace v2

This workspace integrates the three uploaded projects with the agreed pipeline:

```text
OpenCV perception + V2X communication
        ↓
Nav2 / Hybrid A* planning layer
        ↓
Polynomial curve smoothing
        ↓
MPPI controller
        ↓
Priority mux
        ↓
/cmd_vel → Gazebo/QCar
```

## Important rule preserved

`v2x_nav2_sim` from `v2x_nav2_jazzy_smac_gazebo` was copied unchanged. All integration changes are in new/adapted packages around it.

## Packages

| Package | Purpose |
|---|---|
| `v2x_nav2_sim` | Unmodified Nav2/Gazebo simulator package. |
| `v2x_opencv_perception` | Adapted OpenCV lane detection from `qcar-master`. Publishes lane data only. No direct `/cmd_vel`. |
| `v2x_emergency` | V2X communication: requests, traffic lights, grants, health. Vehicle node now reads `/odom`. |
| `v2x_mppi_lane_avoidance` | Polynomial path fitting + MPPI path follower. Renamed from misleading MPC naming. |
| `emergency_priority` | Priority mux and optional V2X safety fallback. Mux is the only package that publishes final `/cmd_vel`. |
| `v2x_system_integration` | Main launch package. |

## Main launch

```bash
cd integrated_ws
colcon build --symlink-install
source install/setup.bash
ros2 launch v2x_system_integration integrated_v2x_nav2_mppi.launch.py
```

## Command topics

Only one node should publish final `/cmd_vel`: `priority_mux_node`.

Inputs to the mux:

```text
/v2x/fallback_cmd_vel   highest priority safety stop
/mppi/cmd_vel           MPPI controller output
/nav2/cmd_vel           Nav2 controller fallback output
```

Output from the mux:

```text
/cmd_vel
```

Nav2 is launched with `/cmd_vel` remapped to `/nav2/cmd_vel`, so Nav2 does not fight the mux.

## OpenCV integration

The old QCar `lane_keeping_node.py` was not kept as a velocity controller because it would fight Nav2/MPPI. Instead:

```text
/qcar/camera/image_raw
        ↓
lane_detection_node
        ↓
/v2x/opencv/lane_pixels
        ↓
lane_path_adapter_node
        ↓
/v2x/opencv/lane_centerline_path
/v2x/opencv/lane_status
```

Note: the current unmodified `v2x_nav2_sim` model appears to expose `/scan`, `/odom`, and `/cmd_vel`, but not a camera topic. The OpenCV nodes are integrated and launchable, but they will wait silently until a camera topic exists or the `camera_topic` parameter is remapped.

## V2X integration

The old V2X vehicle node expected `/vehicle/pose`. In this workspace it uses `/odom`, matching the Nav2/Gazebo simulator.

V2X topics:

```text
/v2x/priority_request
/v2x/signal_status
/v2x/priority_grant
/v2x/health
```

## What was intentionally removed or neutralized

- Old direct lane controller behavior that published velocity commands.
- Old `/QCar/cmd_vel` and `/vehicle/pose` assumptions.
- Misleading `/mpc/cmd_vel` naming. It is now `/mppi/cmd_vel`.
- Legacy pose-publisher demo behavior that conflicted with Gazebo `/odom`.

