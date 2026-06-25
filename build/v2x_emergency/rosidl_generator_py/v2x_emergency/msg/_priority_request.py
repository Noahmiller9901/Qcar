# generated from rosidl_generator_py/resource/_idl.py.em
# with input from v2x_emergency:msg/PriorityRequest.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PriorityRequest(type):
    """Metaclass of message 'PriorityRequest'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('v2x_emergency')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'v2x_emergency.msg.PriorityRequest')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__priority_request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__priority_request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__priority_request
            cls._TYPE_SUPPORT = module.type_support_msg__msg__priority_request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__priority_request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PriorityRequest(metaclass=Metaclass_PriorityRequest):
    """Message class 'PriorityRequest'."""

    __slots__ = [
        '_vehicle_id',
        '_urgency_level',
        '_distance_to_intersection',
        '_estimated_arrival_time',
        '_intersection_id',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'vehicle_id': 'string',
        'urgency_level': 'int32',
        'distance_to_intersection': 'float',
        'estimated_arrival_time': 'float',
        'intersection_id': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.vehicle_id = kwargs.get('vehicle_id', str())
        self.urgency_level = kwargs.get('urgency_level', int())
        self.distance_to_intersection = kwargs.get('distance_to_intersection', float())
        self.estimated_arrival_time = kwargs.get('estimated_arrival_time', float())
        self.intersection_id = kwargs.get('intersection_id', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.vehicle_id != other.vehicle_id:
            return False
        if self.urgency_level != other.urgency_level:
            return False
        if self.distance_to_intersection != other.distance_to_intersection:
            return False
        if self.estimated_arrival_time != other.estimated_arrival_time:
            return False
        if self.intersection_id != other.intersection_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def vehicle_id(self):
        """Message field 'vehicle_id'."""
        return self._vehicle_id

    @vehicle_id.setter
    def vehicle_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'vehicle_id' field must be of type 'str'"
        self._vehicle_id = value

    @builtins.property
    def urgency_level(self):
        """Message field 'urgency_level'."""
        return self._urgency_level

    @urgency_level.setter
    def urgency_level(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'urgency_level' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'urgency_level' field must be an integer in [-2147483648, 2147483647]"
        self._urgency_level = value

    @builtins.property
    def distance_to_intersection(self):
        """Message field 'distance_to_intersection'."""
        return self._distance_to_intersection

    @distance_to_intersection.setter
    def distance_to_intersection(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'distance_to_intersection' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance_to_intersection' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance_to_intersection = value

    @builtins.property
    def estimated_arrival_time(self):
        """Message field 'estimated_arrival_time'."""
        return self._estimated_arrival_time

    @estimated_arrival_time.setter
    def estimated_arrival_time(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'estimated_arrival_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'estimated_arrival_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._estimated_arrival_time = value

    @builtins.property
    def intersection_id(self):
        """Message field 'intersection_id'."""
        return self._intersection_id

    @intersection_id.setter
    def intersection_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'intersection_id' field must be of type 'str'"
        self._intersection_id = value
