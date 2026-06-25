// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from v2x_emergency:msg/SignalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/signal_status.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__BUILDER_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "v2x_emergency/msg/detail/signal_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace v2x_emergency
{

namespace msg
{

namespace builder
{

class Init_SignalStatus_time_remaining
{
public:
  explicit Init_SignalStatus_time_remaining(::v2x_emergency::msg::SignalStatus & msg)
  : msg_(msg)
  {}
  ::v2x_emergency::msg::SignalStatus time_remaining(::v2x_emergency::msg::SignalStatus::_time_remaining_type arg)
  {
    msg_.time_remaining = std::move(arg);
    return std::move(msg_);
  }

private:
  ::v2x_emergency::msg::SignalStatus msg_;
};

class Init_SignalStatus_current_phase
{
public:
  explicit Init_SignalStatus_current_phase(::v2x_emergency::msg::SignalStatus & msg)
  : msg_(msg)
  {}
  Init_SignalStatus_time_remaining current_phase(::v2x_emergency::msg::SignalStatus::_current_phase_type arg)
  {
    msg_.current_phase = std::move(arg);
    return Init_SignalStatus_time_remaining(msg_);
  }

private:
  ::v2x_emergency::msg::SignalStatus msg_;
};

class Init_SignalStatus_intersection_id
{
public:
  Init_SignalStatus_intersection_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SignalStatus_current_phase intersection_id(::v2x_emergency::msg::SignalStatus::_intersection_id_type arg)
  {
    msg_.intersection_id = std::move(arg);
    return Init_SignalStatus_current_phase(msg_);
  }

private:
  ::v2x_emergency::msg::SignalStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::v2x_emergency::msg::SignalStatus>()
{
  return v2x_emergency::msg::builder::Init_SignalStatus_intersection_id();
}

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__BUILDER_HPP_
