#include <aSTLino.h>
#include <arduino/rgb_strip.hpp>
#include <arduino/stream.hpp>


arduino::digitalOut<13> led;

void setup() {
  led.begin();

  Serial.begin(9600);
  Serial << led.to_string() << endl;
}

void loop() {
  led.write(false); 
  delay(250);
  led.write(true); 
  delay(250);
}
