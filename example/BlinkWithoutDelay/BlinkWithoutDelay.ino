#include "BlinkWithoutDelay.h"

BlinkWithoutDelay test;

void setup() {
  test.begin();
}
void loop () {
  test.update();
}

