cmake_minimum_required(VERSION 3.8)
project(v2x_emergency)

find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ── Custom messages ──────────────────────────────────────────
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/PriorityRequest.msg"
  "msg/SignalStatus.msg"
  "msg/PriorityGrant.msg"
  DEPENDENCIES std_msgs
)

# ── Python nodes ─────────────────────────────────────────────
install(PROGRAMS
  v2x_emergency/vehicle_node.py
  v2x_emergency/traffic_light_node.py
  v2x_emergency/v2x_controller.py
  DESTINATION lib/${PROJECT_NAME}
)

# ── Rename executables (drop .py extension) ──────────────────
install(PROGRAMS
  v2x_emergency/vehicle_node.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME vehicle_node
)
install(PROGRAMS
  v2x_emergency/traffic_light_node.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME traffic_light_node
)
install(PROGRAMS
  v2x_emergency/v2x_controller.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME v2x_controller
)

# ── Launch files ─────────────────────────────────────────────
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

ament_package()
