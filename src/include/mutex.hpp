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

#ifndef __STL_HPP_LOCKED__
#define __STL_HPP_LOCKED__
/*
#include "lock_base.hpp"
#include "common.hpp"


namespace std
{
    class mutex : public lock_base
    {
    public:
        using native_handle_type = Sys::mutex_type*;
        
        mutex(Sys::mutex_init_t type = Sys::mutex_init_t::Default, 
              bool shared = false, bool robust = false);
        virtual ~mutex();
        
        void lock( void );
        bool try_lock( void );
	void unlock( void );
           
        native_handle_type native_handle();
        
        mutex& operator=(const mutex& m);
        mutex(const mutex& m);
    private:
        native_handle_type _m_locked;
    };
   
    
    #define LOCK(m) if (std::lock_util<std::mutex> __csc = std::lock_util<std::mutex>(&m))
}
*/
#endif

