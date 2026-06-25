// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from v2x_emergency:msg/PriorityGrant.idl
// generated code does not contain a copyright notice

#include "v2x_emergency/msg/detail/priority_grant__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_v2x_emergency
const rosidl_type_hash_t *
v2x_emergency__msg__PriorityGrant__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb8, 0x4f, 0xca, 0xd1, 0x52, 0x91, 0x74, 0x17,
      0x85, 0xc8, 0xe3, 0xb6, 0x21, 0x80, 0x07, 0x11,
      0x08, 0x97, 0xa0, 0x5e, 0xac, 0x42, 0x1f, 0xb4,
      0xf8, 0x59, 0x3e, 0x3d, 0x52, 0xae, 0x5d, 0x75,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char v2x_emergency__msg__PriorityGrant__TYPE_NAME[] = "v2x_emergency/msg/PriorityGrant";

// Define type names, field names, and default values
static char v2x_emergency__msg__PriorityGrant__FIELD_NAME__intersection_id[] = "intersection_id";
static char v2x_emergency__msg__PriorityGrant__FIELD_NAME__vehicle_id[] = "vehicle_id";
static char v2x_emergency__msg__PriorityGrant__FIELD_NAME__granted[] = "granted";
static char v2x_emergency__msg__PriorityGrant__FIELD_NAME__reason[] = "reason";
static char v2x_emergency__msg__PriorityGrant__FIELD_NAME__green_duration[] = "green_duration";

static rosidl_runtime_c__type_description__Field v2x_emergency__msg__PriorityGrant__FIELDS[] = {
  {
    {v2x_emergency__msg__PriorityGrant__FIELD_NAME__intersection_id, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityGrant__FIELD_NAME__vehicle_id, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityGrant__FIELD_NAME__granted, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityGrant__FIELD_NAME__reason, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {v2x_emergency__msg__PriorityGrant__FIELD_NAME__green_duration, 14, 14},
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
v2x_emergency__msg__PriorityGrant__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {v2x_emergency__msg__PriorityGrant__TYPE_NAME, 31, 31},
      {v2x_emergency__msg__PriorityGrant__FIELDS, 5, 5},
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
  "string vehicle_id\n"
  "bool granted\n"
  "string reason\n"
  "float32 green_duration";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
v2x_emergency__msg__PriorityGrant__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {v2x_emergency__msg__PriorityGrant__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 91, 91},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
v2x_emergency__msg__PriorityGrant__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *v2x_emergency__msg__PriorityGrant__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
