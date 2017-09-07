/*
 * The MIT License
 *
 * Copyright 2016 annas.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   lock_base.hpp
 * Author: annas
 *
 * Created on 17. November 2016, 21:08
 */

#ifndef LOCK_BASE_HPP
#define LOCK_BASE_HPP

#include "common.hpp"
#include "config.h"

namespace std
{
    ///@brief abstract base class for loking   
    class lock_base
    {
    public:
        lock_base() { }
        virtual ~lock_base() { }
        ///@brief abstract function lock the current context
        virtual void lock( void ) = 0;
        ///@brief abstract function try to lock the current context 
        virtual bool try_lock() = 0;
        ///@brief abstract function unlock the current locked context
	virtual void unlock( void ) = 0;
    private:
        lock_base(const lock_base&) { }
        lock_base& operator=(const lock_base&) { }
    };
    
    class alock : public lock_base {
    public:
        alock() { m_locked = false; }
        virtual ~alock() { }
        ///@brief function lock the current context
        virtual void lock( void )  { m_locked = true; noInterrupts(); }
        ///@brief arduino function try to lock the current context 
        virtual bool try_lock() { if(m_locked) return false; else lock(); return true; }
        ///@brief arduino function unlock the current locked context
	virtual void unlock( void ) { if(m_locked) { m_locked = false; interrupts(); } }
    private:
        bool m_locked;
    };
     
    template < class T = std::lock_base> void lock(T* m1) { m1->lock(); }
    template < class T = std::lock_base> void unlock(T* m1) { m1->unlock(); }
    template < class T = std::lock_base> void try_lock(T* m1) { m1->try_lock(); }
     
    ///@brief lock util for auto lock and unlock.
    ///using: if(lock_util<std::mutex>(&varMutex)) { //locked } //and her unlocked
    ///@tparam T lock class
    template <class T = std::lock_base> 
    class lock_util
    {
        public:
            ///@brief Constructor auto lock the context 
            explicit lock_util(T* rc) :  m_rc(rc) 
            { 
                if(m_rc != 0)
                 m_rc->lock();
            }
            ///@brief auto unlock
            ~lock_util(void) 
            {
                m_rc->unlock();
            }
            ///@brief return true when the object not null - helper for if  
            operator bool() { return m_rc != 0; }
        private:
            T*		m_rc;
    };
    
    
}


#endif /* LOCK_BASE_HPP */

