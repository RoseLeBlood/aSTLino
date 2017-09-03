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
 * File:   atomic.hpp
 * Author: annas
 *
 * Created on 8. November 2016, 15:01
 */

#ifndef _STL_ATOMIC_HPP_
#define _STL_ATOMIC_HPP_


#include "algorithm.hpp"

namespace std
{
    namespace MemoryOrder 
    {
        enum MemoryOrder_t {
            Relaxed = __ATOMIC_RELAXED,
            Consume = __ATOMIC_CONSUME,
            Acquire = __ATOMIC_ACQUIRE,
            Release = __ATOMIC_RELEASE,
            AcqRel = __ATOMIC_ACQ_REL,
            SeqCst = __ATOMIC_SEQ_CST
        };
    }
    template <typename T > class atomic 
    {
        public:
            using value_type = T;
            using self_type = atomic<value_type>;
            
            atomic() : _m_value(0) { }
            atomic(value_type value) : _m_value(value) { }
           
       
            value_type get() { return _m_value; }
            
            bool is_free (void) const
                { return __atomic_is_lock_free (sizeof(value_type), &_m_value); }
            void store (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst)
                { __atomic_store_n (&_m_value, v, order); }

            value_type load (MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst) const
                { return __atomic_load_n (&_m_value, order); }
            value_type exchange (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst)
                { return __atomic_exchange_n (&_m_value, v, order); }
            bool compare_exchange (value_type& expected, T desired, bool b, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst)
                { return __atomic_compare_exchange_n (&_m_value, &expected, desired, b, order, order); }

            value_type fetch_add (T v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_fetch_add (&_m_value, v, order); }

            value_type fetch_sub (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_fetch_sub (&_m_value, v, order); }

            value_type fetch_and (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_fetch_and (&_m_value, v, order); }

            value_type fetch_or (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_fetch_or (&_m_value, v, order); }

            value_type fetch_xor (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_fetch_xor (&_m_value, v, order); }

            value_type add_fetch (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                 { return __atomic_add_fetch (&_m_value, v, order); }

            value_type sub_fetch (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                 { return __atomic_sub_fetch (&_m_value, v, order); }

            value_type and_fetch (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_and_fetch (&_m_value, v, order); }

            value_type or_fetch (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_or_fetch (&_m_value, v, order); }

            value_type xor_fetch (value_type v, MemoryOrder::MemoryOrder_t order = MemoryOrder::SeqCst )
                { return __atomic_xor_fetch (&_m_value, v, order); }
            
            void swap(self_type& other) {
                std::swap<value_type>(_m_value, other._m_value);
            }
            
            inline                      operator value_type (void) const	
                { return load(); }
            inline value_type		operator= (value_type v)		
                { store(v); return v; }
            inline value_type		operator++ (int)	
                { return fetch_add (1); }
            inline value_type		operator-- (int)	
                { return fetch_sub (1); }
            inline value_type		operator++ (void)	
                { return add_fetch (1); }
            inline value_type		operator-- (void)	
                { return sub_fetch (1); }
            inline value_type		operator+= (value_type v)	
                { return add_fetch (v); }
            inline value_type		operator-= (value_type v)	
                { return sub_fetch (v); }
            inline value_type		operator&= (value_type v)	
                { return and_fetch (v); }
            inline value_type		operator|= (value_type v)	
                { return or_fetch (v); }
            inline value_type		operator^= (value_type v)	
                { return xor_fetch (v); }
        private:
            atomic& operator= (const atomic&) {}
             atomic (const atomic&) {}
        private:
            T _m_value;
    };
    
}

#endif /* ATOMIC_HPP */

