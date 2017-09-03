/*
 * The MIT License
 *
 * Copyright 2017 annas.
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
 * File:   lock_ptr.hpp
 * Author: annas
 *
 * Created on 18. April 2017, 20:23
 */

#ifndef LOCK_PTR_HPP
#define LOCK_PTR_HPP

#include "lock_base.hpp"

namespace std {
    ///@brief auto lock pointer. 
    ///@tparam T pointer type of this lock pointer
    ///@tparam L lock class @see alock 
    template <typename T, class L = alock>
    class lock_ptr {
    public:
        using value_type = T;
        using lock_type = L;
        using pointer = T*;
        using reference = T&;
        using self_type = lock_ptr<T, L>;
        ///@brief constructor make the pointer and auto lock
        ///@param v Reference to locked area/object 
        ///@param m LockType Reference to the using lock hekper class
        explicit lock_ptr(volatile T& v, lock_type& m) 
            : m_ptr(const_cast<T*>(&v)), m_lock(&m) {
            m_lock->lock();
        }
        ///@brief decunstructor and auto unlock the pointer
        ~lock_ptr() {
            m_lock->unlock();
        }
        ///@brief get the pointer value const
        value_type const *get() const {
            return m_ptr; 
        }
        ///@brief get the pointer value 
        value_type *get() { 
            return m_ptr; 
        }
        ///@brief return the reference of the pointer
        value_type &operator *() { 
            return *m_ptr; 
        }
        ///@brief helper to use this pointer as "native" pointer
        value_type *operator->() { 
            return m_ptr; 
        }
        lock_ptr(const lock_ptr&) = delete;
        lock_ptr& operator = (const lock_ptr&) = delete;
    private:
        pointer m_ptr;
        lock_type *m_lock;
    };
}


#endif /* LOCK_PTR_HPP */

