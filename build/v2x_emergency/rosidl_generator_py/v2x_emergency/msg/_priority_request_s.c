// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from v2x_emergency:msg/PriorityRequest.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "v2x_emergency/msg/detail/priority_request__struct.h"
#include "v2x_emergency/msg/detail/priority_request__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool v2x_emergency__msg__priority_request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[52];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("v2x_emergency.msg._priority_request.PriorityRequest", full_classname_dest, 51) == 0);
  }
  v2x_emergency__msg__PriorityRequest * ros_message = _ros_message;
  {  // vehicle_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "vehicle_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->vehicle_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // urgency_level
    PyObject * field = PyObject_GetAttrString(_pymsg, "urgency_level");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->urgency_level = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // distance_to_intersection
    PyObject * field = PyObject_GetAttrString(_pymsg, "distance_to_intersection");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->distance_to_intersection = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // estimated_arrival_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "estimated_arrival_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->estimated_arrival_time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // intersection_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "intersection_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->intersection_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * v2x_emergency__msg__priority_request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of PriorityRequest */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("v2x_emergency.msg._priority_request");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "PriorityRequest");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  v2x_emergency__msg__PriorityRequest * ros_message = (v2x_emergency__msg__PriorityRequest *)raw_ros_message;
  {  // vehicle_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->vehicle_id.data,
      strlen(ros_message->vehicle_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "vehicle_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // urgency_level
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->urgency_level);
    {
      int rc = PyObject_SetAttrString(_pymessage, "urgency_level", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // distance_to_intersection
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->distance_to_intersection);
    {
      int rc = PyObject_SetAttrString(_pymessage, "distance_to_intersection", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // estimated_arrival_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->estimated_arrival_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "estimated_arrival_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // intersection_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->intersection_id.data,
      strlen(ros_message->intersection_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "intersection_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
