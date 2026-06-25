// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice
#include "v2x_emergency/msg/detail/priority_request__rosidl_typesupport_fastrtps_cpp.hpp"
#include "v2x_emergency/msg/detail/priority_request__functions.h"
#include "v2x_emergency/msg/detail/priority_request__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace v2x_emergency
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
cdr_serialize(
  const v2x_emergency::msg::PriorityRequest & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: vehicle_id
  cdr << ros_message.vehicle_id;

  // Member: urgency_level
  cdr << ros_message.urgency_level;

  // Member: distance_to_intersection
  cdr << ros_message.distance_to_intersection;

  // Member: estimated_arrival_time
  cdr << ros_message.estimated_arrival_time;

  // Member: intersection_id
  cdr << ros_message.intersection_id;

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  v2x_emergency::msg::PriorityRequest & ros_message)
{
  // Member: vehicle_id
  cdr >> ros_message.vehicle_id;

  // Member: urgency_level
  cdr >> ros_message.urgency_level;

  // Member: distance_to_intersection
  cdr >> ros_message.distance_to_intersection;

  // Member: estimated_arrival_time
  cdr >> ros_message.estimated_arrival_time;

  // Member: intersection_id
  cdr >> ros_message.intersection_id;

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
get_serialized_size(
  const v2x_emergency::msg::PriorityRequest & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: vehicle_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.vehicle_id.size() + 1);

  // Member: urgency_level
  {
    size_t item_size = sizeof(ros_message.urgency_level);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: distance_to_intersection
  {
    size_t item_size = sizeof(ros_message.distance_to_intersection);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: estimated_arrival_time
  {
    size_t item_size = sizeof(ros_message.estimated_arrival_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: intersection_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.intersection_id.size() + 1);

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
max_serialized_size_PriorityRequest(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: vehicle_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // Member: urgency_level
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: distance_to_intersection
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: estimated_arrival_time
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: intersection_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = v2x_emergency::msg::PriorityRequest;
    is_plain =
      (
      offsetof(DataType, intersection_id) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
cdr_serialize_key(
  const v2x_emergency::msg::PriorityRequest & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: vehicle_id
  cdr << ros_message.vehicle_id;

  // Member: urgency_level
  cdr << ros_message.urgency_level;

  // Member: distance_to_intersection
  cdr << ros_message.distance_to_intersection;

  // Member: estimated_arrival_time
  cdr << ros_message.estimated_arrival_time;

  // Member: intersection_id
  cdr << ros_message.intersection_id;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
get_serialized_size_key(
  const v2x_emergency::msg::PriorityRequest & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: vehicle_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.vehicle_id.size() + 1);

  // Member: urgency_level
  {
    size_t item_size = sizeof(ros_message.urgency_level);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: distance_to_intersection
  {
    size_t item_size = sizeof(ros_message.distance_to_intersection);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: estimated_arrival_time
  {
    size_t item_size = sizeof(ros_message.estimated_arrival_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: intersection_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.intersection_id.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_emergency
max_serialized_size_key_PriorityRequest(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: vehicle_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: urgency_level
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: distance_to_intersection
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: estimated_arrival_time
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: intersection_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = v2x_emergency::msg::PriorityRequest;
    is_plain =
      (
      offsetof(DataType, intersection_id) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _PriorityRequest__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const v2x_emergency::msg::PriorityRequest *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _PriorityRequest__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<v2x_emergency::msg::PriorityRequest *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _PriorityRequest__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const v2x_emergency::msg::PriorityRequest *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _PriorityRequest__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_PriorityRequest(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _PriorityRequest__callbacks = {
  "v2x_emergency::msg",
  "PriorityRequest",
  _PriorityRequest__cdr_serialize,
  _PriorityRequest__cdr_deserialize,
  _PriorityRequest__get_serialized_size,
  _PriorityRequest__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _PriorityRequest__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_PriorityRequest__callbacks,
  get_message_typesupport_handle_function,
  &v2x_emergency__msg__PriorityRequest__get_type_hash,
  &v2x_emergency__msg__PriorityRequest__get_type_description,
  &v2x_emergency__msg__PriorityRequest__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace v2x_emergency

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_v2x_emergency
const rosidl_message_type_support_t *
get_message_type_support_handle<v2x_emergency::msg::PriorityRequest>()
{
  return &v2x_emergency::msg::typesupport_fastrtps_cpp::_PriorityRequest__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, v2x_emergency, msg, PriorityRequest)() {
  return &v2x_emergency::msg::typesupport_fastrtps_cpp::_PriorityRequest__handle;
}

#ifdef __cplusplus
}
#endif
