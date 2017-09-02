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
 * File:   alignment.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:32
 */

#ifndef _STD_ALIGNMENT_H_
#define _STD_ALIGNMENT_H_

#include "common.hpp"
#include <stddef.h>

namespace std
{
	namespace internal
	{
	#pragma warning(push)

	        template<typename T>
	        struct alignof_helper
	        {
	                char    x;
	                T 		y;
	        };

	    struct __attribute__ ((aligned (16))) aligned16 { uint64_t member[2]; } ;
	    
	#pragma warning(pop)
	        template<size_t N> struct type_with_alignment
	        {
	                typedef char err_invalid_alignment[N > 0 ? -1 : 1];
	        };
	        template<> struct type_with_alignment<0> {};
	        template<> struct type_with_alignment<1> { uint8_t member; };
	        template<> struct type_with_alignment<2> { uint16_t member; };
	        template<> struct type_with_alignment<4> { uint32_t member; };
	        template<> struct type_with_alignment<8> { uint64_t member; };
	        template<> struct type_with_alignment<16> { aligned16 member; };
	}
	template<typename T>
	struct aligof
	{
	        enum 
	        {
	                res = offsetof(internal::alignof_helper<T>, y)
	        };
	};
	template<typename T>
	struct aligned_as
	{
	        typedef typename internal::type_with_alignment<aligof<T>::res> res;
	};

}

#endif


