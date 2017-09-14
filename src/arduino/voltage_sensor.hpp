#ifndef __ASTL_ARDUINOVOLTAGESENSOR_HPP__
#define __ASTL_ARDUINOVOLTAGESENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class voltage_sensor : public isensor {
    public:
      voltage_sensor () {
        setType(sensor_type::Voltage);
      }

      float volts() const { return m_fVolts; } 
    protected:
      float m_fVolts;
  };
}

#endif
