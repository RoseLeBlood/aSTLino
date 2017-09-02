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
 * File:   stack_allocator.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:46
 */

#ifndef _STL_STACK_ALLOCATOR_H_
#define _STL_STACK_ALLOCATOR_H_

#include "common.hpp"

namespace std
{
	// Stack based allocator.
	// Traits:
	//      - operates on buffer of TBytes bytes of stack memory
	//      - never frees memory
	//      - cannot be copied
	template<int TBytes> class stack_allocator
	{
	public:
	        explicit stack_allocator(const char* name = "stack")
	        	: m_name(name), m_bufferTop(0)
	        {
	                /**/
	        }

	        void* allocate(size_t bytes, int flags = 0)
	        {
	                assert(m_bufferTop + bytes <= TBytes);
	                char* ret = &m_buffer[0] + m_bufferTop;
	                m_bufferTop += bytes;
	                return ret;
	        }
	        void deallocate(void* ptr, size_t bytes)
	        {
	                assert(ptr == 0 || (ptr >= &m_buffer[0] && ptr < &m_buffer[TBytes]));
	                sizeof(ptr);
	        }

	        const char* get_name() const    { return m_name; }

	private:
	        stack_allocator(const stack_allocator&);
	        stack_allocator& operator=(const stack_allocator&);

	        const char*     m_name;
	        char            m_buffer[TBytes];
	        size_t          m_bufferTop;
	};
} 
#endif 


