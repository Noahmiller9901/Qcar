#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to v2x_emergency__msg__PriorityRequest

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PriorityRequest {

    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicle_id: std::string::String,


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
    pub intersection_id: std::string::String,

}



impl Default for PriorityRequest {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PriorityRequest::default())
  }
}

impl rosidl_runtime_rs::Message for PriorityRequest {
  type RmwMsg = super::msg::rmw::PriorityRequest;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        vehicle_id: msg.vehicle_id.as_str().into(),
        urgency_level: msg.urgency_level,
        distance_to_intersection: msg.distance_to_intersection,
        estimated_arrival_time: msg.estimated_arrival_time,
        intersection_id: msg.intersection_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        vehicle_id: msg.vehicle_id.as_str().into(),
      urgency_level: msg.urgency_level,
      distance_to_intersection: msg.distance_to_intersection,
      estimated_arrival_time: msg.estimated_arrival_time,
        intersection_id: msg.intersection_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      vehicle_id: msg.vehicle_id.to_string(),
      urgency_level: msg.urgency_level,
      distance_to_intersection: msg.distance_to_intersection,
      estimated_arrival_time: msg.estimated_arrival_time,
      intersection_id: msg.intersection_id.to_string(),
    }
  }
}


// Corresponds to v2x_emergency__msg__SignalStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SignalStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub intersection_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_phase: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub time_remaining: f32,

}



impl Default for SignalStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SignalStatus::default())
  }
}

impl rosidl_runtime_rs::Message for SignalStatus {
  type RmwMsg = super::msg::rmw::SignalStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        intersection_id: msg.intersection_id.as_str().into(),
        current_phase: msg.current_phase.as_str().into(),
        time_remaining: msg.time_remaining,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        intersection_id: msg.intersection_id.as_str().into(),
        current_phase: msg.current_phase.as_str().into(),
      time_remaining: msg.time_remaining,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      intersection_id: msg.intersection_id.to_string(),
      current_phase: msg.current_phase.to_string(),
      time_remaining: msg.time_remaining,
    }
  }
}


// Corresponds to v2x_emergency__msg__PriorityGrant

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PriorityGrant {

    // This member is not documented.
    #[allow(missing_docs)]
    pub intersection_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicle_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub granted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub green_duration: f32,

}



impl Default for PriorityGrant {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PriorityGrant::default())
  }
}

impl rosidl_runtime_rs::Message for PriorityGrant {
  type RmwMsg = super::msg::rmw::PriorityGrant;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        intersection_id: msg.intersection_id.as_str().into(),
        vehicle_id: msg.vehicle_id.as_str().into(),
        granted: msg.granted,
        reason: msg.reason.as_str().into(),
        green_duration: msg.green_duration,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        intersection_id: msg.intersection_id.as_str().into(),
        vehicle_id: msg.vehicle_id.as_str().into(),
      granted: msg.granted,
        reason: msg.reason.as_str().into(),
      green_duration: msg.green_duration,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      intersection_id: msg.intersection_id.to_string(),
      vehicle_id: msg.vehicle_id.to_string(),
      granted: msg.granted,
      reason: msg.reason.to_string(),
      green_duration: msg.green_duration,
    }
  }
}


