#ifndef __ASTL_ARDUINOORIENTATION_HPP__
#define __ASTL_ARDUINOORIENTATION_HPP__

#include "sensor_interface.hpp"

namespace arduino {
  class orientation_sensor : public isensor {
    public:
      orientation_sensor() {
        setType(sensor_type::Orientation);
      }
      sensor_vector& orientation() const { return m_orientation; }
    protected:
		sensor_vector m_orientation;
  };
}

#endif
