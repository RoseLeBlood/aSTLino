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
 * File:   auto_ptr.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:41
 */

#ifndef _STD_AUTO_PTR_H
#define _STD_AUTO_PTR_H

#include "common.hpp"
#include "string.hpp"

namespace std
{
    class __auto_ptr_base 
    {
    public:
        void  set(const volatile void* p) { 
            _M_p = const_cast<void*>(p); 
	}
	void  set(void* p) { 
            _M_p = p; 
	}
    protected:
        void* _M_p;
    };
   
    template<class T> 
    class auto_ptr_ref 
    {
    public:
        using value_type = T;
        using self_type = auto_ptr_ref<T>;
        using pointer = T*;
        using ref_type =  __auto_ptr_base;
           
        auto_ptr_ref(ref_type& r, pointer p) 
            : m_ref(r), m_pointer(p)  {  }

        pointer release() const 
            {  m_ref.set((void*)NULL);  return m_pointer; }
        
        self_type& operator = (self_type const&) = delete;
            
        ref_type& m_ref;
        pointer const m_pointer;
    };
        
    template<class T> 
    class auto_ptr : public __auto_ptr_base
    {
    public:
        
    public:
	using value_type = T;
        using pointer = T*;
	using self_type = auto_ptr<value_type> ;

	explicit auto_ptr(value_type* px = 0) 
            { this->set(px); }
        
	template<class To> 
        auto_ptr(auto_ptr<To>& r)  
            { pointer conversionCheck = r.release(); this->set(conversionCheck); }
        
	auto_ptr(const self_type& r)  
            { this->set(r.release()); }
        
	auto_ptr(auto_ptr_ref<value_type> r) 
            { this->set(r.release());  }
        
	~auto_ptr()  
            { delete this->get(); }
        
	pointer release()  
            { pointer px = this->get(); this->set((void*)0); return px; }
	void reset(pointer px = 0) { 
            pointer pt = this->get();
	    if (px != pt) delete pt;
            this->set(px);
	}

	pointer operator->() const  {
            assert(get() != 0);
            return this->get();
	}
	value_type& operator*() const  {
            assert(get() != 0);
            return *this->get();
	}
	self_type& operator=(auto_ptr_ref<value_type> r)  {
            reset(r.release());
            return *this;
	}
	self_type& operator=(self_type& r)  {
            reset(r.release());
            return *this;
	}
        
	template<class T1> 
        operator auto_ptr_ref<T1>() { 
            return auto_ptr_ref<T1>(*this, this->get()); 
	}
        
	template<class T1> 
        operator auto_ptr<T1>() { 
            return auto_ptr<T1>(release()); 
	}
        value_type* get() const { 
            return static_cast<value_type*>(_M_p); 
	}
        
    };
}

#endif 

