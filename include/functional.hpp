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
 * File:   functional.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:56
 */

#ifndef _STD_FUNCTIONAL_H_
#define _STD_FUNCTIONAL_H_

namespace std
{
	template<typename T> struct less
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs < rhs;
	        }
	};
	template<typename T> struct greater
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs > rhs;
	        }
	};
	template<typename T> struct equal_to
	{
	        bool operator()(const T& lhs, const T& rhs) const
	        {
	                return lhs == rhs;
	        }
	};
        template <typename T> T nexthigher(T k) 
        {
            k--;
            for (unsigned int i=1; i< sizeof(T) * 8; i <<= 1)
                k |= (k >> i);
            return k+1;
        }


}
#endif 
