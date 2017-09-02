/*
 * The MIT License
 *
 * Copyright 2017 annas.
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
 * File:   pallocator.hpp
 * Author: annas
 *
 * Created on 22. April 2017, 23:35
 */

#ifndef PALLOCATOR_HPP
#define PALLOCATOR_HPP

#include "memory/palloc.h"

namespace std {
    
    class pallocator {
    public:
	explicit allocator(const char* name = "palloc") : m_name(name) {}
	~allocator() {}
        
        virtual void* allocate(unsigned int bytes, int flags = 0) {
            unsigned bnum = (unsigned) ((bytes + 1) / (PALLOC_SIZE * 1024)) + 1; 
            return palloc(bnum);
        }
        virtual void* allocate_aligned(unsigned int bytes, unsigned int alignment, int flags = 0) {
            return 0;
        }
	virtual void deallocate(void* ptr, unsigned int bytes) {
            return pfree(ptr);
        }
	const char* get_name() const { return m_name; }
    private:
        const char* m_name;
    };
    inline bool operator==(const pallocator& lhs, const pallocator& rhs) {
	return !strcmp(lhs.get_name(), rhs.get_name());
    }
    inline bool operator!=(const pallocator& lhs, const pallocator& rhs) {
	return !(lhs == rhs);
    }

}

#endif /* PALLOCATOR_HPP */

