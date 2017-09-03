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
 * File:   simple_string_storage.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:59
 */

#ifndef _STD_SIMPLE_STRING_STORAGE_H_
#define _STD_SIMPLE_STRING_STORAGE_H_

#include "common.hpp"


namespace std
{
	template<typename E, class TAllocator> class simple_string_storage
	{
	public:
            using value_type = E;
            using size_type = int;
            using allocator_type = TAllocator;
            using const_iterator = const value_type*       ;
            static const unsigned long      kGranularity = 32;      

        explicit simple_string_storage(const allocator_type& allocator)
        	: m_length(0), m_allocator(allocator)
        {
           	m_data = construct_string(0, m_capacity);
        }
        simple_string_storage(const value_type* str, const allocator_type& allocator)
        	: m_allocator(allocator)
        {
            const int len = strlen(str);
            m_data = construct_string(len, m_capacity);
            std::Sys::MemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }
        simple_string_storage(const value_type* str, size_type len, const allocator_type& allocator)
        	: m_allocator(allocator)
        {
            m_data = construct_string(len, m_capacity);
            std::Sys::MemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }
        simple_string_storage(size_type len, const allocator_type& allocator)
        	: m_allocator(allocator)
        {
            m_data = construct_string(len, m_capacity);
            m_length = len;
            m_data[len] = 0;
        }
        simple_string_storage(const simple_string_storage& rhs, const allocator_type& allocator)
        	: m_data(0), m_capacity(0), m_length(0), m_allocator(allocator)
        {
        	assign(rhs.c_str(), rhs.length());
        }
        ~simple_string_storage()        
        {
      		release_string();
        }

    	simple_string_storage& operator=(const simple_string_storage& rhs)
        {
            if (m_data != rhs.c_str()) 
            {
                    assign(rhs.c_str(), rhs.length());
            }
            return *this;
        }
        
        void assign(const value_type* str, size_type len)
        {
            //assert(str != m_data);
            if (m_capacity <= len + 1)
            {
                    release_string();
                    m_data = construct_string(len, m_capacity);
            }
            std::Sys::MemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }
        void resize(size_type len)
        {
            const size_type prevLen = length();
            const size_type newLen = len;
            if (m_capacity <= newLen + 1)
            {
                    size_type newCapacity;
                    value_type* newData = construct_string(newLen, newCapacity);
                    std::Sys::MemCpy(newData, m_data, prevLen * sizeof(value_type));
                    release_string();
        			m_data = newData;
                    m_capacity = newCapacity;
            }
            m_data[newLen] = 0;
            m_length = newLen;
            assert(invariant());
        }

        void append(const value_type* str, size_type len)
        {
            const size_type prevLen = length();
            const size_type newLen = prevLen + len;
            if (m_capacity <= newLen + 1)
            {
                    size_type newCapacity;
                    value_type* newData = construct_string(newLen, newCapacity);
                    Sys::MemCpy(newData, m_data, prevLen * sizeof(value_type));
                    release_string();
        			m_data = newData;
                    m_capacity = newCapacity;
            }
            Sys::MemCpy(m_data + prevLen, str, len * sizeof(value_type));
            m_data[newLen] = 0;
            m_length = newLen;
            assert(invariant());
        }

        inline const value_type* c_str() const
        {
         	return m_data;
        }
        
    	inline size_type length() const
        {
         	return m_length;
        }
    
    	inline size_type capacity() const { return m_capacity; }
    
	    void clear() 
	    {
	        release_string();
	        m_data = construct_string(0, m_capacity);
	        m_length = 0;
	    }
    
        const allocator_type& get_allocator() const     { return m_allocator; }

        void make_unique(size_type) {}
        value_type* get_data() { return m_data; }

	protected:
		bool invariant() const
		{
		        assert(m_data);
		        assert(m_length <= m_capacity);
		        if (length() != 0)
		                assert(m_data[length()] == 0);
		        return true;
		}
	private:
	    value_type* construct_string(size_type capacity, size_type& out_capacity)
	    {  
	        value_type* data(0);
	        if (capacity != 0)
	        {
	            capacity = (capacity+kGranularity-1) & ~(kGranularity-1);
	            if (capacity < kGranularity)
	                capacity = kGranularity;

	            const size_type toAlloc = sizeof(value_type)*(capacity + 1);
	            void* mem = m_allocator.allocate(toAlloc);
	            data = static_cast<value_type*>(mem);
	        }
	        else    // empty string, no allocation needed. Use our internal buffer.
	        {
	            data = &m_end_of_data;
	        }
	    
	        out_capacity = capacity;
	        *data = 0;
	        return data;
	    }
	    void release_string()
	    {
	            if (m_capacity != 0)
	            {
	                    assert(m_data != &m_end_of_data);
	                    m_allocator.deallocate(m_data, m_capacity);
	            }
	    }
	private:
	    E*              m_data;
	    E               m_end_of_data;
	    size_type       m_capacity;
	    size_type       m_length;
	    TAllocator      m_allocator;
	};

	template<typename E, class TAllocator> class simple_wstring_storage
	{
	public:
            using value_type = E;
            using size_type = int;
            using allocator_type = TAllocator;
            using const_iterator = const value_type*;
            static const unsigned long kGranularity = 32;      

        explicit simple_wstring_storage(const allocator_type& allocator)
        	: m_length(0), m_allocator(allocator)
        {
           	m_data = construct_string(0, m_capacity);
        }
        simple_wstring_storage(const value_type* str, const allocator_type& allocator)
        	: m_allocator(allocator)
        {
            const int len = wcslen(str);
            m_data = construct_string(len, m_capacity);
            Sys::wMemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }
        simple_wstring_storage(const value_type* str, size_type len, const allocator_type& allocator)
        	: m_allocator(allocator)
        {
            m_data = construct_string(len, m_capacity);
            Sys::wMemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }
        simple_wstring_storage(const simple_wstring_storage & rhs, const allocator_type& allocator)
        	: m_data(0), m_capacity(0), m_length(0), m_allocator(allocator)
        {
        	assign(rhs.c_str(), rhs.length());
        }
        ~simple_wstring_storage()        
        {
      		release_string();
        }

    	simple_wstring_storage& operator=(const simple_wstring_storage& rhs)
        {
            if (m_data != rhs.c_str()) 
            {
                    assign(rhs.c_str(), rhs.length());
            }
            return *this;
        }
        
        void assign(const value_type* str, size_type len)
        {
            //assert(str != m_data);
            if (m_capacity <= len + 1)
            {
                    release_string();
                    m_data = construct_string(len, m_capacity);
            }
            Sys::wMemCpy(m_data, str, len*sizeof(value_type));
            m_length = len;
            m_data[len] = 0;
        }

        void append(const value_type* str, size_type len)
        {
            const size_type prevLen = length();
            const size_type newLen = prevLen + len;
            if (m_capacity <= newLen + 1)
            {
                    size_type newCapacity;
                    value_type* newData = construct_string(newLen, newCapacity);
                    Sys::wMemCpy(newData, m_data, prevLen * sizeof(value_type));
                    release_string();
        			m_data = newData;
                    m_capacity = newCapacity;
            }
            Sys::wMemCpy(m_data + prevLen, str, len * sizeof(value_type));
            m_data[newLen] = 0;
            m_length = newLen;
            assert(invariant());
        }

        inline const value_type* c_str() const
        {
         	return m_data;
        }
        
    	inline size_type length() const
        {
         	return m_length;
        }
    
    	inline size_type capacity() const { return m_capacity; }
    
	    void clear() 
	    {
	        release_string();
	        m_data = construct_string(0, m_capacity);
	        m_length = 0;
	    }
    
        const allocator_type& get_allocator() const     { return m_allocator; }

        void make_unique(size_type) {}
        value_type* get_data() { return m_data; }

	protected:
		bool invariant() const
		{
		        assert(m_data);
		        assert(m_length <= m_capacity);
		        if (length() != 0)
		                assert(m_data[length()] == 0);
		        return true;
		}
	private:
	    value_type* construct_string(size_type capacity, size_type& out_capacity)
	    {  
	        value_type* data(0);
	        if (capacity != 0)
	        {
	            capacity = (capacity+kGranularity-1) & ~(kGranularity-1);
	            if (capacity < kGranularity)
	                capacity = kGranularity;

	            const size_type toAlloc = sizeof(value_type)*(capacity + 1);
	            void* mem = m_allocator.allocate(toAlloc);
	            data = static_cast<value_type*>(mem);
	        }
	        else    // empty string, no allocation needed. Use our internal buffer.
	        {
	            data = &m_end_of_data;
	        }
	    
	        out_capacity = capacity;
	        *data = 0;
	        return data;
	    }
	    void release_string()
	    {
	            if (m_capacity != 0)
	            {
	                    assert(m_data != &m_end_of_data);
	                    m_allocator.deallocate(m_data, m_capacity);
	            }
	    }
	private:
	    E*              m_data;
	    E               m_end_of_data;
	    size_type       m_capacity;
	    size_type       m_length;
	    TAllocator      m_allocator;
	};
} 

#endif


