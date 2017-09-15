#ifndef __ASTL_ARDUINO_MPU6050_HPP__
#define __ASTL_ARDUINO_MPU6050_HPP__

#include "sensor_interface.hpp"

#include<Wire.h>

namespace arduino {
  class mpu6050_sensor : public isensor {
    public:
      mpu6050_sensor(int32_t addrs = 0x68) { 
        setName(std::string("MPU6050"));
        setID(addrs);
        setType((int)sensor_type::GyroScope | (int)sensor_type::Temperatur | (int)sensor_type::Accelerator);
       
      }
      virtual void begin()  { 
       // Wire.begin();
        Wire.beginTransmission((uint8_t)getID());
        Wire.write(0x6B);  // PWR_MGMT_1 register
        Wire.write(0);     // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
      }
      virtual void update() { 
        Wire.beginTransmission((uint8_t)getID());
        Wire.write(0x3B);  
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t)getID(),14,true);  
        m_accel.x = Wire.read()<<8|Wire.read();     
        m_accel.y = Wire.read()<<8|Wire.read();  
        m_accel.z = Wire.read()<<8|Wire.read();  
        m_fCelsius = (Wire.read()<<8|Wire.read()) / 340.00+36.53;  
        m_gyro.x = Wire.read()<<8|Wire.read();  
        m_gyro.y = Wire.read()<<8|Wire.read();  
        m_gyro.z =Wire.read()<<8|Wire.read();  
      }
	  float                     celsius() const { return m_fCelsius; }
	  std::math::vector3<float> gyro() const { return m_gyro; }
	  std::math::vector3<float> accel() const { return m_accel; }
	private:
	  std::math::vector3<float> m_accel, m_gyro;
	  float m_fCelsius;
  };
}


#endif
