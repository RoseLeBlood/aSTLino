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
 * File:   iterator.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:29
 */

#ifndef _STD_ITERATOR_H_
#define _STD_ITERATOR_H_

#include "common.hpp"

namespace std
{

	//-----------------------------------------------------------------------------
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	//-----------------------------------------------------------------------------
	template<typename IterT>
	struct iterator_traits 
	{
	   typedef typename IterT::iterator_category iterator_category;
	};

	template<typename T>          
	struct iterator_traits<T*> 
	{
	   typedef random_access_iterator_tag iterator_category;
	};

	//-----------------------------------------------------------------------------
	namespace internal
	{
	        template<typename TIter, typename TDist> inline
	        void distance(TIter first, TIter last, TDist& dist, std::random_access_iterator_tag)
	        {
	                dist = TDist(last - first);
	        }
	        template<typename TIter, typename TDist> inline
	        void distance(TIter first, TIter last, TDist& dist, std::input_iterator_tag)
	        {
	                dist = 0;
	                while (first != last)
	                {
	                        ++dist;
	                        ++first;
	                }
	        }

	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::random_access_iterator_tag)
	        {
	                iter += d;
	        }
	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::bidirectional_iterator_tag)
	        {
	                if (d >= 0)
	                {
	                        while (d--)
	                                ++iter;
	                }
	                else
	                {
	                        while (d++)
	                                --iter;
	                }
	        }
	        template<typename TIter, typename TDist> inline
	        void advance(TIter& iter, TDist d, std::input_iterator_tag)
	        {
	                assert(d >= 0);
	                while (d--)
	                        ++iter;
	        }
	} 
}
#endif

