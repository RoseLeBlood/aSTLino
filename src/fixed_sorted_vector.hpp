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
 * File:   fixed_sorted_vector.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:38
 */

#ifndef _STD_FIXED_SORTED_VECTOR_H_
#define _STD_FIXED_SORTED_VECTOR_H_

#include "fixed_vector.hpp"
#include "sorted_vector.hpp"

namespace std
{
	template<typename TKey, typename TValue,  int TCapacity, bool TGrowOnOverflow, class TCompare = std::less<TKey>, class TAllocator = std::allocator>
		class fixed_sorted_vector : public sorted_vector<TKey, TValue, TCompare, TAllocator, fixed_vector_storage<pair<TKey, TValue>, TAllocator, TCapacity, TGrowOnOverflow> >
	{
	public:
		explicit fixed_sorted_vector(const allocator_type& allocator = allocator_type())
			: sorted_vector(allocator)
		{
		}
	};
}


#endif 


