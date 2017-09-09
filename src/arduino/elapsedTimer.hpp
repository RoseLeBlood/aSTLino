#include <event.hpp>

namespace arduino {
  class timerEventArgs : public std::eventArgs {
  public:
  private:    
  };
  
  class elapsedTimer : public std::object {
    public:
      using Elapsed = std::event<timerEventArgs>;

      elapsedTimer() { }
      elapsedTimer(std::string name, int intervall = 1000)
        : m_strName(name), m_iIntervall(intervall) {}
  
      void begin() {
          m_ulMillis = millis();
      }
      void update() {
        if( (millis() - m_ulMillis) >= m_iIntervall) {
          onElapsed();
          m_ulMillis = millis();
        }
      }
    public:
      Elapsed OnElapsed;
    protected:
      void onElapsed() {
        OnElapsed(this, timerEventArgs());
      }
    private:
      unsigned int  m_iIntervall;
      unsigned long m_ulMillis; 
      std::string   m_strName;
  };
}
