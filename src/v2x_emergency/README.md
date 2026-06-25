# v2x_emergency integrated package

This package keeps the V2X communication layer from `qcar-master` and adapts it to the Nav2/Gazebo stack.

## Topics

- `/v2x/priority_request` — vehicle asks for priority at an intersection
- `/v2x/signal_status` — traffic light phase/status JSON
- `/v2x/priority_grant` — traffic light grants/denies priority
- `/v2x/health` — controller heartbeat/status

## Important integration change

The original QCar files used `/vehicle/pose`. That conflicts with the integrated simulator architecture, so `vehicle_node` now subscribes to `/odom` by default.

The V2X layer does not directly drive the car. It only publishes communication/status data. Emergency stop behavior is handled separately by `emergency_priority/v2x_fallback_node.py`, and final velocity arbitration is handled by `priority_mux_node.py`.
