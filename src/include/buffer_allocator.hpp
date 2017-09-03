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
 * File:   buffer_allocator.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:39
 */

#ifndef _STD_BUFFER_ALLOCATOR_H_
#define _STD_BUFFER_ALLOCATOR_H_

#include "common.hpp"

namespace std
{
	class buffer_allocator 
	{
	public:
	        explicit buffer_allocator(const char* name, char* mem, size_t bufferSize)
	        	: m_name(name), m_buffer(mem), m_bufferTop(0), m_bufferSize(bufferSize)
	        {
	        }

	        void* allocate(size_t bytes, int flags = 0)
	        {
	                assert(m_bufferTop + bytes <= m_bufferSize);
	                char* ret = m_buffer + m_bufferTop;
	                m_bufferTop += bytes;
	                return ret;
	        }
	        void deallocate(void* ptr, size_t bytes)
	        {
	                assert(ptr == 0 || (ptr >= m_buffer && ptr < m_buffer + m_bufferSize));
	                sizeof(ptr);
	        }

	        const char* get_name() const    { return m_name; }

	private:
	        const char*     m_name;
	        char*           m_buffer;
	        size_t          m_bufferTop;
	        size_t          m_bufferSize;
	};
}
#endif 



