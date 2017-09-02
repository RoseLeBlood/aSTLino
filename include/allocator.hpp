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
 * File:   allocator.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:37
 */

#ifndef _STD_ALLOCATOR_H_
#define _STD_ALLOCATOR_H_

#include <string.h>
#include "common.hpp"


namespace std
{
	class allocator 
	{
	public:
	        explicit allocator(const char* name = "alloc"):       m_name(name) {}
	        ~allocator() {}


	        virtual void* allocate(unsigned int bytes, int flags = 0);
	     
	        virtual void* allocate_aligned(unsigned int bytes, unsigned int alignment, int flags = 0)
                {
                    //return memalign(bytes, alignment);
                    return 0;
                }
	        virtual void deallocate(void* ptr, unsigned int bytes);

	        const char* get_name() const { return m_name; }
	private:
	        const char*     m_name;
	};

	inline bool operator==(const allocator& lhs, const allocator& rhs)
	{
	        return !strcmp(lhs.get_name(), rhs.get_name());
	}
	inline bool operator!=(const allocator& lhs, const allocator& rhs)
	{
	        return !(lhs == rhs);
	}

	inline void* allocator::allocate(unsigned int bytes, int)
	{
	        return operator new(bytes);
	}

	inline void allocator::deallocate(void* ptr, unsigned int)
	{
	        operator delete(ptr);
	}
        
        
}

#endif


