// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from v2x_emergency:msg/PriorityGrant.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_grant.h"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_H_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'intersection_id'
// Member 'vehicle_id'
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PriorityGrant in the package v2x_emergency.
typedef struct v2x_emergency__msg__PriorityGrant
{
  rosidl_runtime_c__String intersection_id;
  rosidl_runtime_c__String vehicle_id;
  bool granted;
  rosidl_runtime_c__String reason;
  float green_duration;
} v2x_emergency__msg__PriorityGrant;

// Struct for a sequence of v2x_emergency__msg__PriorityGrant.
typedef struct v2x_emergency__msg__PriorityGrant__Sequence
{
  v2x_emergency__msg__PriorityGrant * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} v2x_emergency__msg__PriorityGrant__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_H_
