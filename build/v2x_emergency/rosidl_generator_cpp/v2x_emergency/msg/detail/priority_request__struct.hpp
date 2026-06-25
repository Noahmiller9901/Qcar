// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_request.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__v2x_emergency__msg__PriorityRequest __attribute__((deprecated))
#else
# define DEPRECATED__v2x_emergency__msg__PriorityRequest __declspec(deprecated)
#endif

namespace v2x_emergency
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PriorityRequest_
{
  using Type = PriorityRequest_<ContainerAllocator>;

  explicit PriorityRequest_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vehicle_id = "";
      this->urgency_level = 0l;
      this->distance_to_intersection = 0.0f;
      this->estimated_arrival_time = 0.0f;
      this->intersection_id = "";
    }
  }

  explicit PriorityRequest_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : vehicle_id(_alloc),
    intersection_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vehicle_id = "";
      this->urgency_level = 0l;
      this->distance_to_intersection = 0.0f;
      this->estimated_arrival_time = 0.0f;
      this->intersection_id = "";
    }
  }

  // field types and members
  using _vehicle_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _vehicle_id_type vehicle_id;
  using _urgency_level_type =
    int32_t;
  _urgency_level_type urgency_level;
  using _distance_to_intersection_type =
    float;
  _distance_to_intersection_type distance_to_intersection;
  using _estimated_arrival_time_type =
    float;
  _estimated_arrival_time_type estimated_arrival_time;
  using _intersection_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _intersection_id_type intersection_id;

  // setters for named parameter idiom
  Type & set__vehicle_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->vehicle_id = _arg;
    return *this;
  }
  Type & set__urgency_level(
    const int32_t & _arg)
  {
    this->urgency_level = _arg;
    return *this;
  }
  Type & set__distance_to_intersection(
    const float & _arg)
  {
    this->distance_to_intersection = _arg;
    return *this;
  }
  Type & set__estimated_arrival_time(
    const float & _arg)
  {
    this->estimated_arrival_time = _arg;
    return *this;
  }
  Type & set__intersection_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->intersection_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    v2x_emergency::msg::PriorityRequest_<ContainerAllocator> *;
  using ConstRawPtr =
    const v2x_emergency::msg::PriorityRequest_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::PriorityRequest_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::PriorityRequest_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__v2x_emergency__msg__PriorityRequest
    std::shared_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__v2x_emergency__msg__PriorityRequest
    std::shared_ptr<v2x_emergency::msg::PriorityRequest_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PriorityRequest_ & other) const
  {
    if (this->vehicle_id != other.vehicle_id) {
      return false;
    }
    if (this->urgency_level != other.urgency_level) {
      return false;
    }
    if (this->distance_to_intersection != other.distance_to_intersection) {
      return false;
    }
    if (this->estimated_arrival_time != other.estimated_arrival_time) {
      return false;
    }
    if (this->intersection_id != other.intersection_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const PriorityRequest_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PriorityRequest_

// alias to use template instance with default allocator
using PriorityRequest =
  v2x_emergency::msg::PriorityRequest_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_REQUEST__STRUCT_HPP_
