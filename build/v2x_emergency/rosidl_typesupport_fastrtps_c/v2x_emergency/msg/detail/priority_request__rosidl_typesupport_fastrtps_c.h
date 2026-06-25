// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice
#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "v2x_emergency/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "v2x_emergency/msg/detail/priority_request__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_serialize_v2x_emergency__msg__PriorityRequest(
  const v2x_emergency__msg__PriorityRequest * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_deserialize_v2x_emergency__msg__PriorityRequest(
  eprosima::fastcdr::Cdr &,
  v2x_emergency__msg__PriorityRequest * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t get_serialized_size_v2x_emergency__msg__PriorityRequest(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t max_serialized_size_v2x_emergency__msg__PriorityRequest(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_serialize_key_v2x_emergency__msg__PriorityRequest(
  const v2x_emergency__msg__PriorityRequest * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t get_serialized_size_key_v2x_emergency__msg__PriorityRequest(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t max_serialized_size_key_v2x_emergency__msg__PriorityRequest(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, v2x_emergency, msg, PriorityRequest)();

#ifdef __cplusplus
}
#endif

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
