#include <aSTLino.h>
#include <arduino/elapsedTimer.hpp>
#include <arduino/rgb_strip.hpp>
#include <arduino/stream.hpp>

class BlinkWithoutDelay {
  public:
    BlinkWithoutDelay()  {
      m_timer = arduino::elapsedTimer(std::string("test"), 1000);
    }
    void begin() {
      m_timer.OnElapsed += new std::delegate<BlinkWithoutDelay, arduino::timerEventArgs>(this, &BlinkWithoutDelay::onTimer_elapsed);
      m_timer.begin();
      m_led.begin();
    }
    void update() {
      m_timer.update();
    }
    void onTimer_elapsed(const std::object *object, arduino::timerEventArgs args) {
      m_ledStatus = !m_ledStatus;
      m_led.write(m_ledStatus);
    }
  private:
    arduino::elapsedTimer m_timer;
    arduino::digitalOut<13> m_led;
    bool m_ledStatus;
};
