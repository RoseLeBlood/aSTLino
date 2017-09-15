#ifndef __ASTL_ARDUINO_MPU9250_HPP__
#define __ASTL_ARDUINO_MPU9250_HPP__

#include "magnetic_sensor.hpp"
#include "accelerator_sensor.hpp"
#include "gyroscope_sensor.hpp"

#include<Wire.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

namespace arduino {
  class mpu9250_sensor : public magnetic_sensor, public accelerator_sensor, public gyroscope_sensor {
    public:
      mpu9250_sensor(uint32_t addrs = MPU9250_ADDRESS) { 
        setName(std::string("MPU9250"));
        setID(addrs);
        setType(sensor_type::GyroScope | sensor_type::MagneticField | sensor_type::Accelerator);
       
      }
      virtual void begin()  { 
        // Set accelerometers low pass filter at 5Hz
        writeByte(getID(),29,0x06);
        // Set gyroscope low pass filter at 5Hz
        writeByte(getID(),26,0x06);
        writeByte(getID(),27,GYRO_FULL_SCALE_1000_DPS);
        // Configure accelerometers range
        writeByte(getID(),28,ACC_FULL_SCALE_4_G);
        // Set by pass mode for the magnetometers
        writeByte(getID(),0x37,0x02);
        // Request continuous magnetometer measurements in 16 bits
        writeByte(MAG_ADDRESS,0x0A,0x16);
      }
      virtual void update() { 
        uint8_t Buf[14], Mag[7];
        uint8_t ST1;
        
        read(getID(),0x3B,14,Buf);

        // Read register Status 1 and wait for the DRDY: Data Ready
        do {
          read(MAG_ADDRESS,0x02,1,&ST1);
        } while (!(ST1&0x01));

        // Read magnetometer data 
        read(MAG_ADDRESS,0x03,7,Mag);
        
        m_accel.x = -(Buf[0]<<8 | Buf[1]);   
        m_accel.y = -(Buf[2]<<8 | Buf[3]);
        m_accel.z = (Buf[4]<<8 | Buf[5]);
       
        m_gyro.x = -(Buf[8]<<8 | Buf[9]); 
        m_gyro.y = -(Buf[10]<<8 | Buf[11]);
        m_gyro.z = (Buf[12]<<8 | Buf[13]); 

        m_mag.x = -(Mag[3]<<8 | Mag[2]);
        m_mag.y = -(Mag[1]<<8 | Mag[0]);
        m_mag.z = -(Mag[5]<<8 | Mag[4]);
      }
    protected: 
      uint8_t read(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
        Wire.beginTransmission(Address);
        Wire.write(Register);
        Wire.endTransmission();
        
        // Read Nbytes
        Wire.requestFrom(Address, Nbytes); 
        uint8_t index=0;
        while (Wire.available())
          Data[index++] = Wire.read();
        return index;
      }
      void writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {
        Wire.beginTransmission(Address);
        Wire.write(Register);
        Wire.write(Data);
        Wire.endTransmission();
      }
  };
}


#endif
