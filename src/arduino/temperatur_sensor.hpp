#ifndef __ASTL_ARDUINOTEMPERATURSENSOR_HPP__
#define __ASTL_ARDUINOTEMPERATURSENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class temperatur_sensor : public isensor {
    public:
      temperatur_sensor () {
        setType(sensor_type::Temperatur);
      }

      float celsius() const { return m_fCelsius; } 
    protected:
      float m_fCelsius;
  };
}

#endif
