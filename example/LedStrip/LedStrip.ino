#include <aSTLino.h>
#include <arduino/rgb_strip.hpp>
#include <arduino/stream.hpp>

arduino::rgb_strip<5,6,3, false> ledstrip; // pin, pin, pin, invert?

void setup() {
  ledstrip.begin();
  ledstrip.color(0,0,0);

  Serial.begin(9600);
  Serial << "LED Strip Demo - Example input \"52 41 78\"" << endl;
}

void loop() {
   
   while (Serial.available() ) {
   int red = Serial.parseInt(); red = (red >255) ? 255 : (red < 0) ? 0 : red;
   int green = Serial.parseInt(); green = (green >255) ? 255 : (green < 0) ? 0 : green;
   int blue = Serial.parseInt(); blue = (blue >255) ? 255 : (blue < 0) ? 0 : blue;

    std::math::colf c = std::math::colf(red,green,blue);
    //Serial << "r:" << c.r << "f g:" << c.g <<"f b:"<<c.b  << "f" << endl;
     
    ledstrip.color(c);
     Serial << ledstrip.to_string() << endl;
   }  
}
