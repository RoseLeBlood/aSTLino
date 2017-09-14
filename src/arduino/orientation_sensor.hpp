#ifndef __ASTL_ARDUINOORIENTATION_HPP__
#define __ASTL_ARDUINOORIENTATION_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class orientation_sensor : public isensor {
    public:
      union {
        struct {
          float Roll;
          float Pitch;
          float Heading;
        };
        struct {
          float x;
          float y;
          float z;
        };
        std::math::vector3<float> xyz;
      }
      orientation_sensor() {
        setType(sensor_type::Orientation);
      }
     
  };
}

#endif
