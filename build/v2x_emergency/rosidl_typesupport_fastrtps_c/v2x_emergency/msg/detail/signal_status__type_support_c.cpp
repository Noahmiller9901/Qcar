// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from v2x_emergency:msg/SignalStatus.idl
// generated code does not contain a copyright notice
#include "v2x_emergency/msg/detail/signal_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "v2x_emergency/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "v2x_emergency/msg/detail/signal_status__struct.h"
#include "v2x_emergency/msg/detail/signal_status__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // current_phase, intersection_id
#include "rosidl_runtime_c/string_functions.h"  // current_phase, intersection_id

// forward declare type support functions


using _SignalStatus__ros_msg_type = v2x_emergency__msg__SignalStatus;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_serialize_v2x_emergency__msg__SignalStatus(
  const v2x_emergency__msg__SignalStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: intersection_id
  {
    const rosidl_runtime_c__String * str = &ros_message->intersection_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: current_phase
  {
    const rosidl_runtime_c__String * str = &ros_message->current_phase;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: time_remaining
  {
    cdr << ros_message->time_remaining;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_deserialize_v2x_emergency__msg__SignalStatus(
  eprosima::fastcdr::Cdr & cdr,
  v2x_emergency__msg__SignalStatus * ros_message)
{
  // Field name: intersection_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->intersection_id.data) {
      rosidl_runtime_c__String__init(&ros_message->intersection_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->intersection_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'intersection_id'\n");
      return false;
    }
  }

  // Field name: current_phase
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->current_phase.data) {
      rosidl_runtime_c__String__init(&ros_message->current_phase);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->current_phase,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'current_phase'\n");
      return false;
    }
  }

  // Field name: time_remaining
  {
    cdr >> ros_message->time_remaining;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t get_serialized_size_v2x_emergency__msg__SignalStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SignalStatus__ros_msg_type * ros_message = static_cast<const _SignalStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: intersection_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->intersection_id.size + 1);

  // Field name: current_phase
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->current_phase.size + 1);

  // Field name: time_remaining
  {
    size_t item_size = sizeof(ros_message->time_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t max_serialized_size_v2x_emergency__msg__SignalStatus(
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

  // Field name: intersection_id
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

  // Field name: current_phase
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

  // Field name: time_remaining
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = v2x_emergency__msg__SignalStatus;
    is_plain =
      (
      offsetof(DataType, time_remaining) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
bool cdr_serialize_key_v2x_emergency__msg__SignalStatus(
  const v2x_emergency__msg__SignalStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: intersection_id
  {
    const rosidl_runtime_c__String * str = &ros_message->intersection_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: current_phase
  {
    const rosidl_runtime_c__String * str = &ros_message->current_phase;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: time_remaining
  {
    cdr << ros_message->time_remaining;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t get_serialized_size_key_v2x_emergency__msg__SignalStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SignalStatus__ros_msg_type * ros_message = static_cast<const _SignalStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: intersection_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->intersection_id.size + 1);

  // Field name: current_phase
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->current_phase.size + 1);

  // Field name: time_remaining
  {
    size_t item_size = sizeof(ros_message->time_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_v2x_emergency
size_t max_serialized_size_key_v2x_emergency__msg__SignalStatus(
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
  // Field name: intersection_id
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

  // Field name: current_phase
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

  // Field name: time_remaining
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = v2x_emergency__msg__SignalStatus;
    is_plain =
      (
      offsetof(DataType, time_remaining) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _SignalStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const v2x_emergency__msg__SignalStatus * ros_message = static_cast<const v2x_emergency__msg__SignalStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_v2x_emergency__msg__SignalStatus(ros_message, cdr);
}

static bool _SignalStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  v2x_emergency__msg__SignalStatus * ros_message = static_cast<v2x_emergency__msg__SignalStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_v2x_emergency__msg__SignalStatus(cdr, ros_message);
}

static uint32_t _SignalStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_v2x_emergency__msg__SignalStatus(
      untyped_ros_message, 0));
}

static size_t _SignalStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_v2x_emergency__msg__SignalStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SignalStatus = {
  "v2x_emergency::msg",
  "SignalStatus",
  _SignalStatus__cdr_serialize,
  _SignalStatus__cdr_deserialize,
  _SignalStatus__get_serialized_size,
  _SignalStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _SignalStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SignalStatus,
  get_message_typesupport_handle_function,
  &v2x_emergency__msg__SignalStatus__get_type_hash,
  &v2x_emergency__msg__SignalStatus__get_type_description,
  &v2x_emergency__msg__SignalStatus__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, v2x_emergency, msg, SignalStatus)() {
  return &_SignalStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
