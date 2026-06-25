// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_request.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__BUILDER_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "v2x_emergency/msg/detail/priority_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace v2x_emergency
{

namespace msg
{

namespace builder
{

class Init_PriorityRequest_intersection_id
{
public:
  explicit Init_PriorityRequest_intersection_id(::v2x_emergency::msg::PriorityRequest & msg)
  : msg_(msg)
  {}
  ::v2x_emergency::msg::PriorityRequest intersection_id(::v2x_emergency::msg::PriorityRequest::_intersection_id_type arg)
  {
    msg_.intersection_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityRequest msg_;
};

class Init_PriorityRequest_estimated_arrival_time
{
public:
  explicit Init_PriorityRequest_estimated_arrival_time(::v2x_emergency::msg::PriorityRequest & msg)
  : msg_(msg)
  {}
  Init_PriorityRequest_intersection_id estimated_arrival_time(::v2x_emergency::msg::PriorityRequest::_estimated_arrival_time_type arg)
  {
    msg_.estimated_arrival_time = std::move(arg);
    return Init_PriorityRequest_intersection_id(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityRequest msg_;
};

class Init_PriorityRequest_distance_to_intersection
{
public:
  explicit Init_PriorityRequest_distance_to_intersection(::v2x_emergency::msg::PriorityRequest & msg)
  : msg_(msg)
  {}
  Init_PriorityRequest_estimated_arrival_time distance_to_intersection(::v2x_emergency::msg::PriorityRequest::_distance_to_intersection_type arg)
  {
    msg_.distance_to_intersection = std::move(arg);
    return Init_PriorityRequest_estimated_arrival_time(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityRequest msg_;
};

class Init_PriorityRequest_urgency_level
{
public:
  explicit Init_PriorityRequest_urgency_level(::v2x_emergency::msg::PriorityRequest & msg)
  : msg_(msg)
  {}
  Init_PriorityRequest_distance_to_intersection urgency_level(::v2x_emergency::msg::PriorityRequest::_urgency_level_type arg)
  {
    msg_.urgency_level = std::move(arg);
    return Init_PriorityRequest_distance_to_intersection(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityRequest msg_;
};

class Init_PriorityRequest_vehicle_id
{
public:
  Init_PriorityRequest_vehicle_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PriorityRequest_urgency_level vehicle_id(::v2x_emergency::msg::PriorityRequest::_vehicle_id_type arg)
  {
    msg_.vehicle_id = std::move(arg);
    return Init_PriorityRequest_urgency_level(msg_);
  }

private:
  ::v2x_emergency::msg::PriorityRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::v2x_emergency::msg::PriorityRequest>()
{
  return v2x_emergency::msg::builder::Init_PriorityRequest_vehicle_id();
}

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__BUILDER_HPP_
