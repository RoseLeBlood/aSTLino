#ifndef __ASTL_ARDUINOACCELSENSOR_HPP__
#define __ASTL_ARDUINOACCELSENSOR_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class accelerator_sensor : public isensor {
    public:
      accelerator_sensor() {
        setType(sensor_type::Accelerator);
      }
	  sensor_vector& accel() const { return m_accel; }
    protected:
		sensor_vector m_accel;
     
  };
}

#endif
