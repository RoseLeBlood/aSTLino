#ifndef __ASTL_ARDUINOMAGNETIC_HPP__
#define __ASTL_ARDUINOMAGNETIC_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class magnetic_sensor : public isensor {
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
      magnetic_sensor() {
        setType(sensor_type::MagneticField);
      }
     
  };
}

#endif
