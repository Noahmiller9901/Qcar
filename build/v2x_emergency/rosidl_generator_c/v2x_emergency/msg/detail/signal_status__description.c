// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from v2x_emergency:msg/SignalStatus.idl
// generated code does not contain a copyright notice

#include "v2x_emergency/msg/detail/signal_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_v2x_emergency
const rosidl_type_hash_t *
v2x_emergency__msg__SignalStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdf, 0x4c, 0x72, 0x88, 0xed, 0x23, 0x15, 0x01,
      0x04, 0x02, 0x7c, 0x93, 0x47, 0x70, 0xd3, 0x66,
      0xa1, 0x68, 0xe3, 0x4f, 0x51, 0xec, 0xe1, 0xd8,
      0x96, 0x0e, 0xfb, 0x24, 0xfd, 0xb9, 0x5f, 0x7c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char v2x_emergency__msg__SignalStatus__TYPE_NAME[] = "v2x_emergency/msg/SignalStatus";

// Define type names, field names, and default values
static char v2x_emergency__msg__SignalStatus__FIELD_NAME__intersection_id[] = "intersection_id";
static char v2x_emergency__msg__SignalStatus__FIELD_NAME__current_phase[] = "current_phase";
static char v2x_emergency__msg__SignalStatus__FIELD_NAME__time_remaining[] = "time_remaining";

static rosidl_runtime_c__type_description__Field v2x_emergency__msg__SignalStatus__FIELDS[] = {
  {
    {v2x_emergency__msg__SignalStatus__FIELD_NAME__intersection_id, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__SignalStatus__FIELD_NAME__current_phase, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__SignalStatus__FIELD_NAME__time_remaining, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
v2x_emergency__msg__SignalStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {v2x_emergency__msg__SignalStatus__TYPE_NAME, 30, 30},
      {v2x_emergency__msg__SignalStatus__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string intersection_id\n"
  "string current_phase\n"
  "float32 time_remaining";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
v2x_emergency__msg__SignalStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {v2x_emergency__msg__SignalStatus__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 67, 67},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
v2x_emergency__msg__SignalStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *v2x_emergency__msg__SignalStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
