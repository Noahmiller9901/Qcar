// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_request.h"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_H_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'vehicle_id'
// Member 'intersection_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PriorityRequest in the package v2x_emergency.
typedef struct v2x_emergency__msg__PriorityRequest
{
  rosidl_runtime_c__String vehicle_id;
  int32_t urgency_level;
  float distance_to_intersection;
  float estimated_arrival_time;
  rosidl_runtime_c__String intersection_id;
} v2x_emergency__msg__PriorityRequest;

// Struct for a sequence of v2x_emergency__msg__PriorityRequest.
typedef struct v2x_emergency__msg__PriorityRequest__Sequence
{
  v2x_emergency__msg__PriorityRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} v2x_emergency__msg__PriorityRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_H_
