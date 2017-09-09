#include "BlinkWithoutDelay.hpp"

BlinkWithoutDelay test;

void setup() {
  test.begin();
}
void loop () {
  test.update();
}

