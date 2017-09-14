#ifndef __ASTL_ARDUINOACCELSENSOR_HPP__
#define __ASTL_ARDUINOACCELSENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class accelerator_sensor : public isensor {
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
      accelerator_sensor() {
        setType(sensor_type::Accelerator);
      }
     
  };
}

#endif
