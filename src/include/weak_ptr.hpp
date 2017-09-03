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
 * File:   weak_ptr.hpp
 * Author: annas
 *
 * Created on 7. Dezember 2016, 23:32
 */

#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "shared_ptr.hpp"


namespace std {
    template <typename T>
    class weak_ptr
    {
    public:
        using value_type = T;
        using ref_type = long;
        using element_type = value_type;
        using pointer = value_type*;
        using const_value_type = const value_type;
        using self_type = weak_ptr<value_type>;
        using shared_type = shared_ptr<value_type>;
        
        explicit weak_ptr(value_type pValue = 0) 
             : _m_ptr(pValue), _m_ref(new atomic<ref_type>(1))  { }
        
        weak_ptr( const self_type& r ) 
            : _m_ptr(r._m_ptr), _m_ref(r._m_ref)  { }
         
        weak_ptr(shared_type pShrd) 
            : _m_ptr(pShrd.get()), _m_ref(new atomic<ref_type>(pShrd.ref())) {}
        
        template <typename other>
        weak_ptr( const weak_ptr<other>& r ) 
            : _m_ptr(r._m_ptr), _m_ref(r._m_ref)  { }
        
        template <typename other>
        weak_ptr( const shared_ptr<other>& pShrd) 
            : _m_ptr(pShrd.get()), _m_ref(new atomic<ref_type>(pShrd.ref())) {}
        
        shared_type lock() {
            return shared_ptr(_m_ptr);
        }
        
        self_type& operator=( const self_type& r ) {
            _m_ptr = r._m_ptr;
            _m_ref = r._m_ref;
            return *this;
        }
        ref_type use_count() const {
            return _m_ref->get();
        }
        const bool expired() {
            return use_count() == 0;
        }
        void reset()  {
            self_type().swap(*this);
        }
        void swap(self_type& other) {
            std::swap<value_type>(_m_ptr, other._m_ptr);
            _m_ref.swap(other._m_ref);
        }
        template<class Y> 
        const bool owner_before( weak_ptr<Y> const & rhs ) {
            return _m_ref < rhs._m_ref;
        }
        template<class Y>
        const bool owner_before( shared_ptr<Y> const & rhs ) {
            return _m_ref < rhs.ref();
        }
        
        pointer operator->() const {
            assert(get() != 0);
            return _m_ptr;
	}
	const_value_type& operator*() {
            assert(get() != 0);
            return *_m_ptr;
	}
        operator bool() {
            return _m_ptr != 0;
        }
    private:
        pointer  _m_ptr;
        atomic<ref_type>* _m_ref;
    };
    template<class TA, class TB> 
    inline bool operator<(const weak_ptr<TA>& a, weak_ptr<TB> const & b) {
        return a.owner_before( b );
    }
    template<class T> 
    void swap(weak_ptr<T>& a, weak_ptr<T>& b) {
        a.swap(b);
    }
}

#endif /* WEAK_PTR_HPP */

