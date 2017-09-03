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
 * File:   save_ptr.hpp
 * Author: annas
 *
 * Created on 11. November 2016, 05:58
 */

#ifndef SAVE_PTR_HPP
#define SAVE_PTR_HPP

#include "common.hpp"

namespace std
{
    template<typename T>
    class save_ptr
    {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using self_type = save_ptr<T>;
        
        save_ptr() : m_ptr(0) {
        }
        explicit save_ptr(T *v) : m_ptr(v) {
        }
        ~save_ptr() {
            if(m_ptr) delete m_ptr;
        }
 
        value_type const *get() const {
            return m_ptr; 
        }
        value_type *get() { 
            return m_ptr; 
        }
 
        value_type const &operator *() const { 
            return *m_ptr; 
        }
        value_type &operator *() { 
            return *m_ptr; 
        }
        value_type const *operator->() const {
            return m_ptr; 
        }
        value_type *operator->() { 
            return m_ptr; 
        }
        value_type *release() { 
            value_type *tmp = m_ptr; 
            m_ptr = NULL; 
            return tmp; 
        }       
        void reset(value_type *p = NULL)
        {
            if(m_ptr) delete m_ptr;
                m_ptr = p;
        }
        void swap(self_type &other)
        {                         
            value_type *tmp = other.m_ptr;
            other.m_ptr = m_ptr;
            m_ptr = tmp;
        }

    private:
        pointer *m_ptr;
        save_ptr(save_ptr const &other) {}
        save_ptr const &operator=(save_ptr const &other) {}
    };
}

#endif /* SAVE_PTR_HPP */

