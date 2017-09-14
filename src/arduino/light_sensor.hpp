#ifndef __ASTL_ARDUINOLIGHTSENSOR_HPP__
#define __ASTL_ARDUINOLIGHTSENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class light_sensor : public isensor {
    public:
      light_sensor () {
        setType(sensor_type::Light);
      }

      float lux() const { return m_fLux; } 
    protected:
      float m_fLux;
  };
}

#endif
