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
 * File:   lock.hpp
 * Author: annas
 *
 * Created on 8. November 2016, 00:08
 */

#ifndef __STL_HPP_SPINLOCK__
#define __STL_HPP_SPINLOCK__
/*
#include "lock_base.hpp"
#include "atomic.hpp"


namespace std
{
    class spinlock : public lock_base
    {
    public:
        using native_handle_type = Sys::spinlk_type*;
        
        spinlock();
        virtual ~spinlock();
        
        void lock( void );
        bool try_lock( void );
	void unlock( void );
           
        native_handle_type native_handle();
        
        spinlock(const spinlock&) = delete;
        spinlock& operator=(const spinlock&) = delete;
    private:
        native_handle_type _m_locked;
    };
    #define SPINLOCK(m) if (std::lock_util<std::spinlock> __csc = std::lock_util<std::spinlock>(&m))


    class atomic_spinlock : public lock_base
    {
    public:
        enum type {Locked, Unlocked };
        using lock_type = atomic_spinlock::type;
        using native_handle_type = atomic_spinlock;
        
        atomic_spinlock() : m_locked() {
            
        }
        ~atomic_spinlock() {
            
        }
        
        void lock( void ) {
           while( m_locked.exchange(Locked, MemoryOrder::Acquire) == Locked) {
               
           }
        }
        bool try_lock( void ) {
            if( m_locked.exchange(Locked, MemoryOrder::Acquire) == Locked)
                return false;
            else
                lock();
            return true;
        }
	void unlock( void ) {
            m_locked.store(Unlocked, MemoryOrder::Release);
        }
           
        native_handle_type& native_handle() {
            return *this;
        }
        
        atomic_spinlock(const atomic_spinlock&) = delete;
        atomic_spinlock& operator=(const atomic_spinlock&) = delete; 
    private:
        std::atomic<type> m_locked;
    };
    
#define ATOMICLOCK(m) if (std::lock_util<std::atomic_spinlock> __csc = \
                          std::lock_util<std::atomic_spinlock>(&m))

}
*/
#endif

