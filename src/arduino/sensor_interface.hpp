#ifndef __ASTL_ARDUINOSENSOR_HPP__
#define __ASTL_ARDUINOSENSOR_HPP__

namespace arduino {
  enum class sensor_type {
    Accelerator = 1, //
    MagneticField = 2,//
    Orientation = 4,//
    GyroScope = 8,//
    Light = 16,//
    Distance = 32,//
    LineareAcceleration = 64,//
    Temperatur = 128,//
    Voltage = 256,//
    Current = 512,//
    Color = 1024
  };
  struct sensor_vector {
	  union {
        struct {
          float Roll;
          float Pitch;
          float Heading;
        };
        struct {
          float x;
          float y;
          float z;
        };
        std::math::vector3<float> xyz;
      };
  };
  class isensor {
    public:
      isensor() { }
      
      virtual void begin()  { }
      virtual void update() { }
      
      virtual void sensor_delay()      { delay(m_iDelay); }
      
      std::string  getName()    { return m_strName; }
      int32_t      getID()      { return m_iId; }
      sensor_type  getType()    { return m_eType; }
      float        getMinValue(){ return m_fMinValue; }
      float        getMaxValue(){ return m_fMaxValue; }
      float        getResolution() { return m_fResolution; }
    protected:
      void setName(std::string name)            { m_strName = name; }
      void setId(int32_t id)                    { m_iId = id; }
      void setType(sensor_type t)               { m_eType = t; }
      void setMinMaxValue(float min, float max) { m_fMinValue = min; m_fMaxValue = max; }
      void setResolution(float resolution)      { m_fResolution = resolution; }
      void setDelay(int32_t delay)              { m_iDelay = delay; }
    private:
      std::string   m_strName;
      int32_t       m_iId;
      sensor_type   m_eType;
      float         m_fMinValue;
      float         m_fMaxValue;
      float         m_fResolution;
      int32_t       m_iDelay;
  };

  
}
#endif
