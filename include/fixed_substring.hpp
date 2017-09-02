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
 * File:   fixed_substring.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:44
 */

#ifndef STD_FIXED_SUBSTRING_H
#define STD_FIXED_SUBSTRING_H

#include "fixed_array.hpp"
#include "string_utils.hpp"

namespace std
{
	// "Substring" of fixed size.
	// Cannot grow.
	// Never allocates memory.
	template<typename E, size_t N> class fixed_substring : private fixed_array<E, N + 1>
	{
            using Base = fixed_array<E, N + 1>;
	public:
            using value_type = E;
            using size_type = size_t;

        fixed_substring()
        {
        	data()[0] = value_type(0);
        }
        explicit fixed_substring(const value_type* str)
        {
         	assign(str);
        }
        template<size_t M>
        fixed_substring(const fixed_substring<E, M>& rhs)
        {
         	assign(rhs.data());
        }

        template<size_t M>
        fixed_substring& operator=(const fixed_substring<E, M>& rhs)
        {
            assign(rhs.data());
            return *this;
        }
        fixed_substring& operator=(const value_type* str)
        {
            assign(str);
            return *this;
        }

        using Base::operator[];
        using Base::data;

        // For std::string compatibility.
        const char* c_str() const
        {
            return data();
        }

        void assign(const value_type* str)
        {
            assert(str != data());
            const size_type len = (size_type)std::strlen(str);
            const size_type toCopy = len < N ? len : N;
            Sys::MemCpy(data(), str, toCopy * sizeof(value_type));
            data()[toCopy] = value_type(0);
        }
        void assign(const fixed_substring& rhs)
        {
            assign(rhs.data());
        }

        void append(const value_type* str)
        {
            const size_type strLen = (size_type)std::strlen(str);
            const size_type ourLen = (size_type)std::strlen(data());
            size_type toAppend = strLen;
            if (ourLen + toAppend > N)
                    toAppend = N - ourLen;
            Sys::MemCpy(data() + ourLen, str, toAppend * sizeof(value_type));
            data()[ourLen + toAppend] = value_type(0);
        }
        void append(const fixed_substring& rhs)
        {
            append(rhs.data());
        }

        size_type find_index_of(value_type ch) const
        {
            size_type retIndex(-1);
            const E* ptr = data();
            size_type currentIndex(0);
            while (*ptr != value_type(0))
            {
                if (*ptr == ch)
                {
                    retIndex = currentIndex;
                    break;
                }
                ++ptr;
                ++currentIndex;
            }
            return retIndex;
        }
        size_type find_index_of_last(value_type ch) const
        {
            size_type retIndex(-1);
            const value_type* ptr = data();
            size_type currentIndex(0);
            while (*ptr != value_type(0))
            {
                if (*ptr == ch)
                  	retIndex = currentIndex;
                ++ptr;
                ++currentIndex;
            }
            return retIndex;
        }
        void trim_end(size_type index)
        {
            if (index >= 0)
            {
                assert(index < (size_type)std::strlen(data()));
                data()[index] = value_type(0);
            }
        }

        bool empty() const
        {
            return length() == 0;
        }
        size_type length() const
        {
         	return std::strlen(data());
        }

        bool operator==(const fixed_substring& rhs) const
        {
       		return std::strcompare(data(), rhs.data()) == 0;
        }
        bool operator!=(const fixed_substring& rhs) const
        {
          	return !(*this == rhs);
        }
	};
} 

#endif


