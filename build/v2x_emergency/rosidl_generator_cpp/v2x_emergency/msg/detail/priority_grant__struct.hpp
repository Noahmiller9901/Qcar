// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from v2x_emergency:msg/PriorityGrant.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/priority_grant.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__v2x_emergency__msg__PriorityGrant __attribute__((deprecated))
#else
# define DEPRECATED__v2x_emergency__msg__PriorityGrant __declspec(deprecated)
#endif

namespace v2x_emergency
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PriorityGrant_
{
  using Type = PriorityGrant_<ContainerAllocator>;

  explicit PriorityGrant_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intersection_id = "";
      this->vehicle_id = "";
      this->granted = false;
      this->reason = "";
      this->green_duration = 0.0f;
    }
  }

  explicit PriorityGrant_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : intersection_id(_alloc),
    vehicle_id(_alloc),
    reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intersection_id = "";
      this->vehicle_id = "";
      this->granted = false;
      this->reason = "";
      this->green_duration = 0.0f;
    }
  }

  // field types and members
  using _intersection_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _intersection_id_type intersection_id;
  using _vehicle_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _vehicle_id_type vehicle_id;
  using _granted_type =
    bool;
  _granted_type granted;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;
  using _green_duration_type =
    float;
  _green_duration_type green_duration;

  // setters for named parameter idiom
  Type & set__intersection_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->intersection_id = _arg;
    return *this;
  }
  Type & set__vehicle_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->vehicle_id = _arg;
    return *this;
  }
  Type & set__granted(
    const bool & _arg)
  {
    this->granted = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }
  Type & set__green_duration(
    const float & _arg)
  {
    this->green_duration = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    v2x_emergency::msg::PriorityGrant_<ContainerAllocator> *;
  using ConstRawPtr =
    const v2x_emergency::msg::PriorityGrant_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::PriorityGrant_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::PriorityGrant_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__v2x_emergency__msg__PriorityGrant
    std::shared_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__v2x_emergency__msg__PriorityGrant
    std::shared_ptr<v2x_emergency::msg::PriorityGrant_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PriorityGrant_ & other) const
  {
    if (this->intersection_id != other.intersection_id) {
      return false;
    }
    if (this->vehicle_id != other.vehicle_id) {
      return false;
    }
    if (this->granted != other.granted) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    if (this->green_duration != other.green_duration) {
      return false;
    }
    return true;
  }
  bool operator!=(const PriorityGrant_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PriorityGrant_

// alias to use template instance with default allocator
using PriorityGrant =
  v2x_emergency::msg::PriorityGrant_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__PRIORITY_GRANT__STRUCT_HPP_
