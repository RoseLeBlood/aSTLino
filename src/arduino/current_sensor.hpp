#ifndef __ASTL_ARDUINOCURRENTSENSOR_HPP__
#define __ASTL_ARDUINOCURRENTSENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class current_sensor : public isensor {
    public:
      current_sensor() {
        setType(sensor_type::Current);
      }

      float milliamps() const { return m_fmA; } 
    protected:
      float m_fmA;
  };
}

#endif
