#ifndef __ASTL_ARDUINOGYROSCOPE_HPP__
#define __ASTL_ARDUINOGYROSCOPE_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class gyroscope_sensor : public isensor {
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
      gyroscope_sensor () {
        setType(sensor_type::GyroScope);
      }
     
  };
}

#endif
