#include <aSTLino.h>
#include <arduino/rgb_strip.hpp>
#include <arduino/stream.hpp>
#include <math/vector3.hpp>
#include <arduino/eeprom.hpp>

//#define EEPROM_CLEAR 0

arduino::rgb_strip<5,6,3, false> ledstrip; // pin, pin, pin, invert?
arduino::digitalOut<13> led;
  
void setup() {
  Serial.begin(9600); 
  #ifdef EEPROM_CLEAR 
    arduino::eeprom::clear(); while(true) {}
    arduino::eeprom::write(std::math::color<float>(0,0,255,128), 1);
  #endif
  
  led.begin();
  ledstrip.begin();

  std::math::color<float> f;
  arduino::eeprom::read(f, 1);
  
  ledstrip.color(f);
 
}
void loop() {
   led.write(false);
   while (Serial.available() ) {
     led.write(true);
     
     int r = Serial.parseInt(); r = (r >255) ? 255 : (r < 0) ? 0 : r;
     int g = Serial.parseInt(); g = (g >255) ? 255 : (g < 0) ? 0 : g;
     int b = Serial.parseInt(); b = (b >255) ? 255 : (b < 0) ? 0 : b;
     int a = Serial.parseInt(); a = (a >255) ? 255 : (a < 0) ? 0 : a;

     ledstrip.fade_color(std::math::color<float>(r, g, b, a), 0.1f, 150);
     
     arduino::eeprom::write(ledstrip.color(), 1);
     Serial << ledstrip.to_string() << endl; 
   }
}  



