#ifndef __ASTL_ARDUINO_MPU6050_HPP__
#define __ASTL_ARDUINO_MPU6050_HPP__

#include "temperatur_sensor.hpp"
#include "accelerator_sensor.hpp"
#include "gyroscope_sensor.hpp"

#include<Wire.h>

namespace arduino {
  class mpu6050_sensor : public temperatur_sensor, public accelerator_sensor, public gyroscope_sensor {
    public:
      mpu6050_sensor(uint32_t addrs = 0x68) { 
        setName(std::string("MPU6050"));
        setID(addrs);
        setType(sensor_type::GyroScope | sensor_type::Temperatur | sensor_type::Accelerator);
       
      }
      virtual void begin()  { 
       // Wire.begin();
        Wire.beginTransmission(getID());
        Wire.write(0x6B);  // PWR_MGMT_1 register
        Wire.write(0);     // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
      }
      virtual void update() { 
        Wire.beginTransmission(getID());
        Wire.write(0x3B);  
        Wire.endTransmission(false);
        Wire.requestFrom(getID(),14,true);  
        m_accel.x = Wire.read()<<8|Wire.read();     
        m_accel.y = Wire.read()<<8|Wire.read();  
        m_accel.z = Wire.read()<<8|Wire.read();  
        m_fCelsius = (Wire.read()<<8|Wire.read()) / 340.00+36.53;  
        m_gyro.x = Wire.read()<<8|Wire.read();  
        m_gyro.y = Wire.read()<<8|Wire.read();  
        m_gyro.z =Wire.read()<<8|Wire.read();  
      }
  };
}


#endif
