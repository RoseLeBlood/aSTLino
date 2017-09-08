#ifndef __ASTL_RGBSTRIP_PIN_HPP__
#define __ASTL_RGBSTRIP_PIN_HPP__

#include "../math/colors.hpp"
#include "arduino_pin.hpp"

namespace arduino {
  template <uint8_t TPR, uint8_t TPG, uint8_t TPB, bool nc>
  class rgb_strip {
    public:
      void begin() { m_r.begin(); m_g.begin(); m_b.begin(); }

      void color(std::math::colf color)  { m_cColor = color; m_r.write(color.r, nc); m_g.write(color.g, nc); m_b.write(color.b, nc);}
      void color(unsigned long col)      { color(std::math::colf(col)); }
      void color(byte r, byte g, byte b) { m_cColor = std::math::colf(r, g, b, 255); m_r.write(r, nc); m_g.write(g, nc); m_b.write(b, nc); }

      std::math::colf color() const      { return m_cColor; }

      template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                return std::basic_string<E, TAllocator, TStorage>("[rgb_strip] ") << 
                       (TPR) << std::basic_string<E, TAllocator, TStorage>(":") << 
                       (TPG) << std::basic_string<E, TAllocator, TStorage>(":") <<
                       (TPB) << std::basic_string<E, TAllocator, TStorage>(" ") << color().to_string() ;
      }
      
    private:
      analogOut<TPR> m_r;
      analogOut<TPG> m_g;
      analogOut<TPB> m_b;
      
      std::math::colf m_cColor;
  };
}
#endif
