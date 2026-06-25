// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from v2x_emergency:msg/SignalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/signal_status.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__TRAITS_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "v2x_emergency/msg/detail/signal_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace v2x_emergency
{

namespace msg
{

inline void to_flow_style_yaml(
  const SignalStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: intersection_id
  {
    out << "intersection_id: ";
    rosidl_generator_traits::value_to_yaml(msg.intersection_id, out);
    out << ", ";
  }

  // member: current_phase
  {
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
    out << ", ";
  }

  // member: time_remaining
  {
    out << "time_remaining: ";
    rosidl_generator_traits::value_to_yaml(msg.time_remaining, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SignalStatus & msg,
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

  // member: current_phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
    out << "\n";
  }

  // member: time_remaining
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_remaining: ";
    rosidl_generator_traits::value_to_yaml(msg.time_remaining, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SignalStatus & msg, bool use_flow_style = false)
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
  const v2x_emergency::msg::SignalStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  v2x_emergency::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use v2x_emergency::msg::to_yaml() instead")]]
inline std::string to_yaml(const v2x_emergency::msg::SignalStatus & msg)
{
  return v2x_emergency::msg::to_yaml(msg);
}

template<>
inline const char * data_type<v2x_emergency::msg::SignalStatus>()
{
  return "v2x_emergency::msg::SignalStatus";
}

template<>
inline const char * name<v2x_emergency::msg::SignalStatus>()
{
  return "v2x_emergency/msg/SignalStatus";
}

template<>
struct has_fixed_size<v2x_emergency::msg::SignalStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<v2x_emergency::msg::SignalStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<v2x_emergency::msg::SignalStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__TRAITS_HPP_
