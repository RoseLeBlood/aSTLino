#ifndef __ASTL_ARDUINOMAGNETIC_HPP__
#define __ASTL_ARDUINOMAGNETIC_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class magnetic_sensor : public isensor {
    public:
      magnetic_sensor() {
        setType(sensor_type::MagneticField);
      }
      sensor_vector& mag() const { return m_mag; }
	
    protected:
		sensor_vector m_mag; 
  };
}

#endif
