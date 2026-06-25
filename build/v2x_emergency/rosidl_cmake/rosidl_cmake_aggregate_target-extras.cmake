# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target v2x_emergency::v2x_emergency
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${v2x_emergency_TARGETS}.
if(v2x_emergency_TARGETS AND NOT TARGET v2x_emergency::v2x_emergency)
  add_library(v2x_emergency::v2x_emergency INTERFACE IMPORTED)
  set_target_properties(v2x_emergency::v2x_emergency PROPERTIES
    INTERFACE_LINK_LIBRARIES "${v2x_emergency_TARGETS}")
endif()
