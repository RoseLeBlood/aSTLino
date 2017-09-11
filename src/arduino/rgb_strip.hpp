#ifndef __ASTL_RGBSTRIP_PIN_HPP__
#define __ASTL_RGBSTRIP_PIN_HPP__

#include "../math/colors.hpp"
#include "arduino_pin.hpp"

namespace arduino {
  template <uint8_t TPR, uint8_t TPG, uint8_t TPB, bool nc>
  class rgb_strip {
    public:
      void begin() { m_r.begin(); m_g.begin(); m_b.begin(); }

      void color(std::math::colf color)                   { m_cColor = color; writeToPin(10); }
      void color(unsigned long col)                       { color(std::math::colf(col)); }
      void color(byte r, byte g, byte b, byte brig = 255) { color(std::math::colf(r, g, b, brig));  }
      
	  void brightniss(float f)                            { m_cColor.a = f; }
	  void brightniss(const int& b) 					  { m_cColor.a = (float)(b / 255.0f); }
	  
      std::math::colf        color()            { return m_cColor; } 
	  
	  float           brightniss()              { return m_cColor.a; }
	  
    void fade_color(std::math::colf color, const float step, const int& del = 10) { 
	    fadeBrigh(color.a, step, del);
		fadeRed(color.r, step, del);
        fadeGreen(color.g, step, del);	
        fadeBlue(color.b, step, del);		
	}
    void fade_color(unsigned long col, float f)              { fade_color(std::math::colf(col), f); }
    void fade_color(byte r, byte g, byte b, byte brig, float f) { fade_color(std::math::colf(r, g, b, brig), f);  }
      
      template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                return std::basic_string<E, TAllocator, TStorage>("[rgb_strip] ") << 
                       (TPR) << std::basic_string<E, TAllocator, TStorage>(":") << 
                       (TPG) << std::basic_string<E, TAllocator, TStorage>(":") <<
                       (TPB) << std::basic_string<E, TAllocator, TStorage>(" ") << color().to_string() ;
      }
	protected:
	  void fadeRed(const float& red, const float& step, const int& del = 10) {
		if(m_cColor.r == red) return;
		float diff = red - m_cColor.red;
		bool  plus = diff >= 0;
        int   steps = plus ? diff / step : -diff / step;
		for(int i = 0; i < steps; i++) { m_cColor.r += plus ? step : -step; writeToPin(del); }
	  }
	  void fadeGreen(const float& green, const float& step, const int& del = 10) {
		if(m_cColor.g == green) return;
		float diff = green - m_cColor.g;
		bool  plus = diff >= 0;
        int   steps = plus ? diff / step : -diff / step;
		for(int i = 0; i < steps; i++) { m_cColor.g += plus ? step : -step; writeToPin(del); }
	  }
	  void fadeBlue(const float& blue, const float& step, const int& del = 10) {
		if(m_cColor.b == blue) return;
		float diff = blue - m_cColor.b;
		bool  plus = diff >= 0;
        int   steps = plus ? diff / step : -diff / step;
		for(int i = 0; i < steps; i++) { m_cColor.b += plus ? step : -step; writeToPin(del); }
	  }
	  void fadeBrigh(const float& brig, const float& step, const int& del = 10) {
		if(m_cColor.a == brig) return;
		float diff = brig - m_cColor.a;
		bool  plus = diff >= 0;
        int   steps = plus ? diff / step : -diff / step;
		for(int i = 0; i < steps; i++) { m_cColor.a += plus ? step : -step; writeToPin(del); }
	  }
	  void writeToPin(const int& del) {
		 m_r.write(m_cColor.r * m_cColor.a, nc); 
		 m_g.write(m_cColor.g * m_cColor.a, nc); 
		 m_b.write(m_cColor.b * m_cColor.a, nc); 
		 delay(del);
	  }
    private:
      analogOut<TPR> m_r;
      analogOut<TPG> m_g;
      analogOut<TPB> m_b;
      
      std::math::colf m_cColor;
  };
}
#endif
