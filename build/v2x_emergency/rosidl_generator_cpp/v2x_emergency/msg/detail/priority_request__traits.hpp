// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_request.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__TRAITS_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "v2x_emergency/msg/detail/priority_request__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace v2x_emergency
{

namespace msg
{

inline void to_flow_style_yaml(
  const PriorityRequest & msg,
  std::ostream & out)
{
  out << "{";
  // member: vehicle_id
  {
    out << "vehicle_id: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_id, out);
    out << ", ";
  }

  // member: urgency_level
  {
    out << "urgency_level: ";
    rosidl_generator_traits::value_to_yaml(msg.urgency_level, out);
    out << ", ";
  }

  // member: distance_to_intersection
  {
    out << "distance_to_intersection: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_to_intersection, out);
    out << ", ";
  }

  // member: estimated_arrival_time
  {
    out << "estimated_arrival_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_arrival_time, out);
    out << ", ";
  }

  // member: intersection_id
  {
    out << "intersection_id: ";
    rosidl_generator_traits::value_to_yaml(msg.intersection_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PriorityRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: vehicle_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vehicle_id: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_id, out);
    out << "\n";
  }

  // member: urgency_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "urgency_level: ";
    rosidl_generator_traits::value_to_yaml(msg.urgency_level, out);
    out << "\n";
  }

  // member: distance_to_intersection
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_to_intersection: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_to_intersection, out);
    out << "\n";
  }

  // member: estimated_arrival_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_arrival_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_arrival_time, out);
    out << "\n";
  }

  // member: intersection_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "intersection_id: ";
    rosidl_generator_traits::value_to_yaml(msg.intersection_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PriorityRequest & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace v2x_emergency

namespace rosidl_generator_traits
{

[[deprecated("use v2x_emergency::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const v2x_emergency::msg::PriorityRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  v2x_emergency::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use v2x_emergency::msg::to_yaml() instead")]]
inline std::string to_yaml(const v2x_emergency::msg::PriorityRequest & msg)
{
  return v2x_emergency::msg::to_yaml(msg);
}

template<>
inline const char * data_type<v2x_emergency::msg::PriorityRequest>()
{
  return "v2x_emergency::msg::PriorityRequest";
}

template<>
inline const char * name<v2x_emergency::msg::PriorityRequest>()
{
  return "v2x_emergency/msg/PriorityRequest";
}

template<>
struct has_fixed_size<v2x_emergency::msg::PriorityRequest>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<v2x_emergency::msg::PriorityRequest>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<v2x_emergency::msg::PriorityRequest>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__TRAITS_HPP_
