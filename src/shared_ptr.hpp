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
 * File:   shared_ptr.hpp
 * Author: annas
 *
 * Created on 8. November 2016, 15:17
 */

#ifndef _STL_SHARED_PTR_HPP_
#define _STL_SHARED_PTR_HPP_

#include "common.hpp"
#include "atomic.hpp"

namespace std
{
    template < typename T > class shared_ptr
    {
        public:
            using value_type = T;
            using ref_type = long;
            using const_value_type = const value_type;
            using pointer = value_type*;
            using self_type = shared_ptr<value_type>;
            
            explicit shared_ptr(pointer ptr ) : _m_ptr(ptr),
                    _m_ref(new atomic<ref_type>(1))  { }
            
            shared_ptr(const self_type& sp) {
                if (++(*_m_ref) != 1) {
                    _m_ptr = sp._m_ptr;
                }
                else
                {
                    //tried to copy a shared pointer targeted for deletion
                }
            }

            ~shared_ptr() { 
                if (--(*_m_ref) == 0) {
                    delete _m_ptr;
                    delete _m_ref;
                }
            }
            pointer release() {
                pointer __px = this->get();
                if (--(*_m_ref) == 0) {
                    delete _m_ptr;
                    delete _m_ref;
                }
                return __px;
            }
            void reset( pointer pValue = 0) 
                { self_type(pValue).swap(*this); }
           
            pointer get() const { 
		return static_cast<T*>(_m_ptr);
	    }

            ref_type ref() {
                return _m_ref->get();
            }
            void swap(self_type& b) {
                std::swap<value_type*>(_m_ptr, b._m_ptr);
                std::swap<atomic<ref_type>*>(_m_ref, b._m_ref);
            }
            self_type& operator = (self_type& sp) {
                release();                
                _m_ptr = sp._m_ptr;
                _m_ref = sp._m_ref;
                return *this;
            }
	    pointer operator->() const {
		assert(get() != 0);
		return this->get();
	    }
	    const_value_type& operator*() {
		assert(get() != 0);
		return *this->get();
	    }
            operator bool() {
                return _m_ptr != 0;
            }
        private:
            pointer  _m_ptr;
            atomic<ref_type>* _m_ref;
    };
}



#endif /* SHARED_PTR_HPP */

