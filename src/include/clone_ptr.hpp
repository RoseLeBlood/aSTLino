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
 * File:   clone_ptr.hpp
 * Author: annas
 *
 * Created on 11. November 2016, 06:19
 */

#ifndef _STL_CLONE_PTR_HPP_
#define _STL_CLONE_PTR_HPP_

#include "common.hpp"
#include "save_ptr.hpp"

namespace std
{
    class clone_ptr_interface
    {
    protected:
        clone_ptr_interface* clone() = 0;
    };
    template<typename T = clone_ptr_interface>
    class clone_ptr 
    {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using self_type = clone_ptr<value_type>;
        using cloneptrinterface = clone_ptr_interface;
        
        clone_ptr() : m_ptr(0) { }
        
        explicit clone_ptr(T *v) : m_ptr(v) { }
        
        clone_ptr(save_ptr const &other) {
            if(other.get() != NULL)
                m_ptr = other->clone();
        }
        clone_ptr const &operator=(clone_ptr const &other) {
            if(other != this) {
                clone_ptr tmp(other);
                swap(tmp);
            }
            return *this;
        }
        ~clone_ptr() {
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
    protected:
        cloneptrinterface* clone()
        {
            if(m_ptr != NULL)
                return m_ptr->clone();
        }
    private:
        pointer *m_ptr;
    };
}
#endif /* CLONE_PTR_HPP */

