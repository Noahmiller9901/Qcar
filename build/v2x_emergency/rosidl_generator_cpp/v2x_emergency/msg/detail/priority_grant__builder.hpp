// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from v2x_emergency:msg/PriorityGrant.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_grant.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__BUILDER_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "v2x_emergency/msg/detail/priority_grant__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace v2x_emergency
{

namespace msg
{

namespace builder
{

class Init_PriorityGrant_green_duration
{
public:
  explicit Init_PriorityGrant_green_duration(::v2x_emergency::msg::PriorityGrant & msg)
  : msg_(msg)
  {}
  ::v2x_emergency::msg::PriorityGrant green_duration(::v2x_emergency::msg::PriorityGrant::_green_duration_type arg)
  {
    msg_.green_duration = std::move(arg);
    return std::move(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityGrant msg_;
};

class Init_PriorityGrant_reason
{
public:
  explicit Init_PriorityGrant_reason(::v2x_emergency::msg::PriorityGrant & msg)
  : msg_(msg)
  {}
  Init_PriorityGrant_green_duration reason(::v2x_emergency::msg::PriorityGrant::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return Init_PriorityGrant_green_duration(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityGrant msg_;
};

class Init_PriorityGrant_granted
{
public:
  explicit Init_PriorityGrant_granted(::v2x_emergency::msg::PriorityGrant & msg)
  : msg_(msg)
  {}
  Init_PriorityGrant_reason granted(::v2x_emergency::msg::PriorityGrant::_granted_type arg)
  {
    msg_.granted = std::move(arg);
    return Init_PriorityGrant_reason(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityGrant msg_;
};

class Init_PriorityGrant_vehicle_id
{
public:
  explicit Init_PriorityGrant_vehicle_id(::v2x_emergency::msg::PriorityGrant & msg)
  : msg_(msg)
  {}
  Init_PriorityGrant_granted vehicle_id(::v2x_emergency::msg::PriorityGrant::_vehicle_id_type arg)
  {
    msg_.vehicle_id = std::move(arg);
    return Init_PriorityGrant_granted(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityGrant msg_;
};

class Init_PriorityGrant_intersection_id
{
public:
  Init_PriorityGrant_intersection_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PriorityGrant_vehicle_id intersection_id(::v2x_emergency::msg::PriorityGrant::_intersection_id_type arg)
  {
    msg_.intersection_id = std::move(arg);
    return Init_PriorityGrant_vehicle_id(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityGrant msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::v2x_emergency::msg::PriorityGrant>()
{
  return v2x_emergency::msg::builder::Init_PriorityGrant_intersection_id();
}

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__BUILDER_HPP_
