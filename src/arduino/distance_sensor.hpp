#ifndef __ASTL_ARDUINODISTANCESENSOR_HPP__
#define __ASTL_ARDUINODISTANCESENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class distance_sensor : public isensor {
    public:
      distance_sensor() {
        setType(sensor_type::Distance);
      }

      float centimeters() const { return m_fcm; } 
    protected:
      float m_fcm;
  };
}

#endif
