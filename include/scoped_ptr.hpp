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
 * File:   scoped_ptr.hpp
 * Author: annas
 *
 * Created on 7. Dezember 2016, 23:03
 */

#ifndef SCOPED_PTR_HPP
#define SCOPED_PTR_HPP

#include "algorithm.hpp"
#include "auto_ptr.hpp"
#include "common.hpp"


namespace std {
    template <typename T>
    class scoped_ptr {
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_value_type = const value_type;
        using self_type = scoped_ptr<value_type>;
        
        explicit scoped_ptr( pointer pValue = 0 ) 
            : m_pPointer( pValue ) { }
        explicit scoped_ptr( const auto_ptr<value_type>& pPtr ) 
            : m_pPointer( pPtr.release() ) { }
        ~scoped_ptr() { }
        
        void swap(self_type& b) {
            std::swap<value_type*>(m_pPointer, b.m_pPointer);
        }
        void reset( pointer pValue = 0) 
            { self_type(pValue).swap(*this); }
        pointer get() 
            { return m_pPointer; }
        
        const pointer operator -> () {
            assert(m_pPointer != 0);
            return m_pPointer;
        }
        const_value_type& operator *() {
            assert(m_pPointer != 0);
            return *m_pPointer;
        }
        operator bool() {
                return m_pPointer != 0;
            }
    private:
        pointer m_pPointer;
    };
    template<class T>
    inline void swap(scoped_ptr<T> & a, scoped_ptr<T> & b) {
        a.swap(b);
    }
}

#endif /* SCOPED_PTR_HPP */

