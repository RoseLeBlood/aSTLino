#ifndef __ASTL_ARDUINO_PIN_HPP__
#define __ASTL_ARDUINO_PIN_HPP__

#include "../string.hpp"

  namespace arduino {

    template<uint8_t TPin, uint8_t TMode>
    class arduino_pin_base {
      public:        
        uint8_t  getPinMode() const { return TMode; }
        uint8_t  getPin()     const { return TPin; }

        unsigned long pulseIn(uint8_t state, unsigned long timeout = 1000000L) { return pulseIn(TPin, state, timeout); }
        unsigned long pulseInLong(uint8_t state, unsigned long timeout = 1000000L) { return pulseInLong(TPin, state, timeout); }
    };
    template<uint8_t TPin, uint8_t TMode = OUTPUT>
    class digital_pin : public arduino_pin_base<TPin, TMode> {
      public:
        digital_pin() { }
        
        virtual void begin()   { pinMode(TPin, TMode); }
        int  read()            { return digitalRead(TPin);  }
        void write(int state, bool b = false)  { digitalWrite(TPin, state); }  
        void write(bool state, bool b = false) { digitalWrite(TPin, state); }  
        void write(float f, bool b = false)    { digitalWrite(TPin, f == 1.0f ); }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                return std::basic_string<E, TAllocator, TStorage>("[digital_pin] ") << TPin << ":" << 
                       ( TMode == OUTPUT ? "Out" : TMode == INPUT ? "Inp" : "Pull") << " " << read();
      }
    };
    template<uint8_t TPin, uint8_t TMode = OUTPUT>
    class analog_pin : public arduino_pin_base<TPin, TMode> {
      public:
        virtual void begin()   { pinMode(TPin, TMode);  }
        int  read()            { return analogRead(TPin);  }
        void write(int state, bool invert)  { 
           int p = constrain(state, 0, 255);
           if(!invert) p = 255 - p;        
           analogWrite(TPin, p); 
        }  
        void write(float f, bool invert = true) { 
           if(f > 1.0f) f = 1.0f; 
           analogWrite(TPin, (int)(f*255.0f)  ); 
         }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                return std::basic_string<E, TAllocator, TStorage>("[analog_pin] ") << TPin << ":" << 
                       ( TMode == OUTPUT ? "Out" : TMode == INPUT ? "Inp" : "Pull") << " " << read();
      }
    };
    
    template<class TC> 
    class arduino_pin : public TC {
      public:
        virtual void begin() { TC::begin(); m_iValue = read();}
        bool changed()       { return m_iValue != read(); }

        
      private:
        int16_t m_iValue;
    };

    template <uint8_t TPin>
    using digitalOut = arduino_pin< digital_pin<TPin, OUTPUT> >;
    template <uint8_t TPin>
    using digitalIn  = arduino_pin< digital_pin<TPin, INPUT>  >;

    template <uint8_t TPin>
    using analogOut = arduino_pin< analog_pin<TPin, OUTPUT> >;
    template <uint8_t TPin>
    using analogIn  = arduino_pin< analog_pin<TPin, INPUT>  >;
  }

#endif
