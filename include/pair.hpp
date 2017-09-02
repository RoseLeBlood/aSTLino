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
 * File:   pair.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 01:07
 */

#ifndef _STD_PAIR_H_
#define _STD_PAIR_H_

#include "type_traits.hpp"

namespace std
{
	template<typename T1, typename T2> struct pair
	{
        using  first_type = T1;
        using second_type = T2;

        pair() 
        {
        }
        pair(const T1& a, const T2& b)
        	: first(a), second(b) 
        {  
        }
        explicit pair(const T1& a)
        	: first(a) 
        {
        }
		pair(const pair<T1,T2>& rhs) 
			: first(rhs.first), second(rhs.second) 
		{
		}
    
    	pair& operator=(const pair<T1,T2>& rhs) 
    	{
    	    first = rhs.first;
    	    second = rhs.second;
    	    return *this;
    	}
    	
        T1      first;
        T2      second;
	};

	template<typename T1, typename T2> struct is_pod<pair<T1, T2> >
	{
	        enum { value = (is_pod<T1>::value || is_fundamental<T1>::value) && 
	                (is_pod<T2>::value || is_fundamental<T2>::value) };
	};
	template<typename T1, typename T2> pair<T1, T2> make_pair(const T1& a, const T2& b)
	{
	        return pair<T1, T2>(a, b);
	}

}
#endif 


