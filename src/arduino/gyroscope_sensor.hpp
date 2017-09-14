#ifndef __ASTL_ARDUINOGYROSCOPE_HPP__
#define __ASTL_ARDUINOGYROSCOPE_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class gyroscope_sensor : public isensor {
    public:
      
      gyroscope_sensor () {
        setType(sensor_type::GyroScope);
      }
	  sensor_vector& gyro() const { return m_gyro; }
    protected:
		sensor_vector m_gyro;
  };
}

#endif
