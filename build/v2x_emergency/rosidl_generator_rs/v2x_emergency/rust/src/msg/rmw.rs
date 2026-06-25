#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "v2x_emergency__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__PriorityRequest() -> *const std::ffi::c_void;
}

#[link(name = "v2x_emergency__rosidl_generator_c")]
extern "C" {
    fn v2x_emergency__msg__PriorityRequest__init(msg: *mut PriorityRequest) -> bool;
    fn v2x_emergency__msg__PriorityRequest__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PriorityRequest>, size: usize) -> bool;
    fn v2x_emergency__msg__PriorityRequest__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PriorityRequest>);
    fn v2x_emergency__msg__PriorityRequest__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PriorityRequest>, out_seq: *mut rosidl_runtime_rs::Sequence<PriorityRequest>) -> bool;
}

// Corresponds to v2x_emergency__msg__PriorityRequest
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PriorityRequest {

    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicle_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub urgency_level: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_to_intersection: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub estimated_arrival_time: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub intersection_id: rosidl_runtime_rs::String,

}



impl Default for PriorityRequest {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !v2x_emergency__msg__PriorityRequest__init(&mut msg as *mut _) {
        panic!("Call to v2x_emergency__msg__PriorityRequest__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PriorityRequest {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityRequest__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityRequest__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityRequest__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PriorityRequest {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PriorityRequest where Self: Sized {
  const TYPE_NAME: &'static str = "v2x_emergency/msg/PriorityRequest";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__PriorityRequest() }
  }
}


#[link(name = "v2x_emergency__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__SignalStatus() -> *const std::ffi::c_void;
}

#[link(name = "v2x_emergency__rosidl_generator_c")]
extern "C" {
    fn v2x_emergency__msg__SignalStatus__init(msg: *mut SignalStatus) -> bool;
    fn v2x_emergency__msg__SignalStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SignalStatus>, size: usize) -> bool;
    fn v2x_emergency__msg__SignalStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SignalStatus>);
    fn v2x_emergency__msg__SignalStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SignalStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<SignalStatus>) -> bool;
}

// Corresponds to v2x_emergency__msg__SignalStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SignalStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub intersection_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_phase: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub time_remaining: f32,

}



impl Default for SignalStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !v2x_emergency__msg__SignalStatus__init(&mut msg as *mut _) {
        panic!("Call to v2x_emergency__msg__SignalStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SignalStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__SignalStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__SignalStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__SignalStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SignalStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SignalStatus where Self: Sized {
  const TYPE_NAME: &'static str = "v2x_emergency/msg/SignalStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__SignalStatus() }
  }
}


#[link(name = "v2x_emergency__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__PriorityGrant() -> *const std::ffi::c_void;
}

#[link(name = "v2x_emergency__rosidl_generator_c")]
extern "C" {
    fn v2x_emergency__msg__PriorityGrant__init(msg: *mut PriorityGrant) -> bool;
    fn v2x_emergency__msg__PriorityGrant__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PriorityGrant>, size: usize) -> bool;
    fn v2x_emergency__msg__PriorityGrant__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PriorityGrant>);
    fn v2x_emergency__msg__PriorityGrant__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PriorityGrant>, out_seq: *mut rosidl_runtime_rs::Sequence<PriorityGrant>) -> bool;
}

// Corresponds to v2x_emergency__msg__PriorityGrant
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PriorityGrant {

    // This member is not documented.
    #[allow(missing_docs)]
    pub intersection_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicle_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub granted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub green_duration: f32,

}



impl Default for PriorityGrant {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !v2x_emergency__msg__PriorityGrant__init(&mut msg as *mut _) {
        panic!("Call to v2x_emergency__msg__PriorityGrant__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PriorityGrant {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityGrant__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityGrant__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_emergency__msg__PriorityGrant__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PriorityGrant {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PriorityGrant where Self: Sized {
  const TYPE_NAME: &'static str = "v2x_emergency/msg/PriorityGrant";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__v2x_emergency__msg__PriorityGrant() }
  }
}


