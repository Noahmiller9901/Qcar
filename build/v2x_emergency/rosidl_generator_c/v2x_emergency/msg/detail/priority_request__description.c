// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice

#include "v2x_emergency/msg/detail/priority_request__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_v2x_emergency
const rosidl_type_hash_t *
v2x_emergency__msg__PriorityRequest__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x73, 0x9e, 0x17, 0xbf, 0x3c, 0x45, 0x5c, 0x0f,
      0x9f, 0xb0, 0x50, 0x9a, 0x64, 0xbe, 0xcc, 0xc4,
      0xe0, 0x55, 0xc0, 0x03, 0x61, 0x16, 0xd3, 0x43,
      0xd7, 0x99, 0xc8, 0x00, 0xc4, 0x17, 0xa3, 0xdc,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char v2x_emergency__msg__PriorityRequest__TYPE_NAME[] = "v2x_emergency/msg/PriorityRequest";

// Define type names, field names, and default values
static char v2x_emergency__msg__PriorityRequest__FIELD_NAME__vehicle_id[] = "vehicle_id";
static char v2x_emergency__msg__PriorityRequest__FIELD_NAME__urgency_level[] = "urgency_level";
static char v2x_emergency__msg__PriorityRequest__FIELD_NAME__distance_to_intersection[] = "distance_to_intersection";
static char v2x_emergency__msg__PriorityRequest__FIELD_NAME__estimated_arrival_time[] = "estimated_arrival_time";
static char v2x_emergency__msg__PriorityRequest__FIELD_NAME__intersection_id[] = "intersection_id";

static rosidl_runtime_c__type_description__Field v2x_emergency__msg__PriorityRequest__FIELDS[] = {
  {
    {v2x_emergency__msg__PriorityRequest__FIELD_NAME__vehicle_id, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityRequest__FIELD_NAME__urgency_level, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityRequest__FIELD_NAME__distance_to_intersection, 24, 24},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityRequest__FIELD_NAME__estimated_arrival_time, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityRequest__FIELD_NAME__intersection_id, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
v2x_emergency__msg__PriorityRequest__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {v2x_emergency__msg__PriorityRequest__TYPE_NAME, 33, 33},
      {v2x_emergency__msg__PriorityRequest__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string vehicle_id\n"
  "int32 urgency_level\n"
  "float32 distance_to_intersection\n"
  "float32 estimated_arrival_time\n"
  "string intersection_id";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
v2x_emergency__msg__PriorityRequest__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {v2x_emergency__msg__PriorityRequest__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 125, 125},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
v2x_emergency__msg__PriorityRequest__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *v2x_emergency__msg__PriorityRequest__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
