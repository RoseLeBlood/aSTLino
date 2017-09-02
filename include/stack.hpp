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
 * File:   stack.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:52
 */

#ifndef _STD_STACK_H_
#define _STD_STACK_H_

#include "vector.hpp"

namespace std
{
	template<typename T, class TAllocator = std::allocator, class TContainer = std::vector<T, TAllocator> >
	class stack
	{
	public:
            using container_type = TContainer;
            using value_type =  TContainer::value_type;
            using size_type =  TContainer::size_type ;
            using allocator_type = TAllocator                      ;

        explicit stack(const allocator_type& allocator = allocator_type())
        	: m_container(allocator)
        {
        }
        stack(const stack& rhs, const allocator_type& allocator = allocator_type())
        	: m_container(rhs, allocator)
        {
        }
        explicit stack(e_noinitialize n)
        	: m_container(n)
        {
        }
        stack& operator=(const stack& rhs)
        {
            if (&rhs != this)
            {
            	m_container = rhs.m_container;
            }
            return *this;
        }

        void push(const value_type& v)
        {
          	m_container.push_back(v);
        }
        void pop()
        {
           	m_container.pop_back();
        }
        value_type& top()                               
        { 
        	return m_container.back(); 
        }
        const value_type& top() const   
        { 
        	return m_container.back(); 
        }

        // @extension
        void clear()                    
        { 
        	m_container.clear(); 
        }

        bool empty() const              
        { 
        	return m_container.empty(); 
        }
        size_type size() const  
        { 
        	return m_container.size(); 
        }
        const allocator_type& get_allocator() const     
        { 
                return m_container.get_allocator(); 
        }
        void set_allocator(const allocator_type& allocator)
        {
                m_container.set_allocator(allocator);
        }
	private:
	    TContainer      m_container;
	};
} 
#endif

