// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from v2x_emergency:msg/SignalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "v2x_emergency/msg/signal_status.hpp"


#ifndef V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__STRUCT_HPP_
#define V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__v2x_emergency__msg__SignalStatus __attribute__((deprecated))
#else
# define DEPRECATED__v2x_emergency__msg__SignalStatus __declspec(deprecated)
#endif

namespace v2x_emergency
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SignalStatus_
{
  using Type = SignalStatus_<ContainerAllocator>;

  explicit SignalStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intersection_id = "";
      this->current_phase = "";
      this->time_remaining = 0.0f;
    }
  }

  explicit SignalStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : intersection_id(_alloc),
    current_phase(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intersection_id = "";
      this->current_phase = "";
      this->time_remaining = 0.0f;
    }
  }

  // field types and members
  using _intersection_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _intersection_id_type intersection_id;
  using _current_phase_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_phase_type current_phase;
  using _time_remaining_type =
    float;
  _time_remaining_type time_remaining;

  // setters for named parameter idiom
  Type & set__intersection_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->intersection_id = _arg;
    return *this;
  }
  Type & set__current_phase(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_phase = _arg;
    return *this;
  }
  Type & set__time_remaining(
    const float & _arg)
  {
    this->time_remaining = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    v2x_emergency::msg::SignalStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const v2x_emergency::msg::SignalStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::SignalStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      v2x_emergency::msg::SignalStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__v2x_emergency__msg__SignalStatus
    std::shared_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__v2x_emergency__msg__SignalStatus
    std::shared_ptr<v2x_emergency::msg::SignalStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SignalStatus_ & other) const
  {
    if (this->intersection_id != other.intersection_id) {
      return false;
    }
    if (this->current_phase != other.current_phase) {
      return false;
    }
    if (this->time_remaining != other.time_remaining) {
      return false;
    }
    return true;
  }
  bool operator!=(const SignalStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SignalStatus_

// alias to use template instance with default allocator
using SignalStatus =
  v2x_emergency::msg::SignalStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace v2x_emergency

#endif  // V2X_EMERGENCY__MSG__DETAIL__SIGNAL_STATUS__STRUCT_HPP_
