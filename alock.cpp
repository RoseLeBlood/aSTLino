#include "include/lock_base.hpp"
#include <Arduino.h>
namespace std {
        ///@brief abstract function lock the current context
        void alock::lock( void ) { m_locked = true; noInterrupts(); }
        ///@brief abstract function try to lock the current context 
        bool alock::try_lock() { if(m_locked) return false; else lock(); return true; }
        ///@brief abstract function unlock the current locked context
        void alock::unlock( void ) { if(m_locked) { m_locked = false; interrupts(); } }
}

