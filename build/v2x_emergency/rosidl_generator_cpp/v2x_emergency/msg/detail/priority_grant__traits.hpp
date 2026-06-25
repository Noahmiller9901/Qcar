// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from v2x_emergency:msg/PriorityGrant.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_grant.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__TRAITS_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "v2x_emergency/msg/detail/priority_grant__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace v2x_emergency
{

namespace msg
{

inline void to_flow_style_yaml(
  const PriorityGrant & msg,
  std::ostream & out)
{
  out << "{";
  // member: intersection_id
  {
    out << "intersection_id: ";
    rosidl_generator_traits::value_to_yaml(msg.intersection_id, out);
    out << ", ";
  }

  // member: vehicle_id
  {
    out << "vehicle_id: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_id, out);
    out << ", ";
  }

  // member: granted
  {
    out << "granted: ";
    rosidl_generator_traits::value_to_yaml(msg.granted, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << ", ";
  }

  // member: green_duration
  {
    out << "green_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.green_duration, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PriorityGrant & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: intersection_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "intersection_id: ";
    rosidl_generator_traits::value_to_yaml(msg.intersection_id, out);
    out << "\n";
  }

  // member: vehicle_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vehicle_id: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_id, out);
    out << "\n";
  }

  // member: granted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "granted: ";
    rosidl_generator_traits::value_to_yaml(msg.granted, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }

  // member: green_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "green_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.green_duration, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PriorityGrant & msg, bool use_flow_style = false)
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
  const v2x_emergency::msg::PriorityGrant & msg,
  std::ostream & out, size_t indentation = 0)
{
  v2x_emergency::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use v2x_emergency::msg::to_yaml() instead")]]
inline std::string to_yaml(const v2x_emergency::msg::PriorityGrant & msg)
{
  return v2x_emergency::msg::to_yaml(msg);
}

template<>
inline const char * data_type<v2x_emergency::msg::PriorityGrant>()
{
  return "v2x_emergency::msg::PriorityGrant";
}

template<>
inline const char * name<v2x_emergency::msg::PriorityGrant>()
{
  return "v2x_emergency/msg/PriorityGrant";
}

template<>
struct has_fixed_size<v2x_emergency::msg::PriorityGrant>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<v2x_emergency::msg::PriorityGrant>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<v2x_emergency::msg::PriorityGrant>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__TRAITS_HPP_
