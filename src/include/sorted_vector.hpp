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
 * File:   sorted_vector.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:55
 */

#ifndef STD_SORTED_VECTOR_H
#define STD_SORTED_VECTOR_H

#include "functional.hpp"
#include "pair.hpp"
#include "sort.hpp"
#include "vector.hpp"

namespace std
{
	namespace internal
	{
	    template<class TPair, class TFunctor>
	    struct compare_func
	    {
	        bool operator()(const TPair& lhs, const TPair& rhs) const
	        {
	                return TFunctor()(lhs.first, rhs.first);
	        }
	        bool operator()(const TPair& lhs, const typename TPair::first_type& rhs) const
	        {
	                return TFunctor()(lhs.first, rhs);
	        }
	        bool operator()(const typename TPair::first_type& lhs, const TPair& rhs) const
	        {
	                return TFunctor()(lhs, rhs.first);
	        }
	    };
	}

	template<typename TKey, typename TValue, class TCompare = std::less<TKey>, class TAllocator = std::allocator, 
        class TStorage = std::standard_vector_storage<pair<TKey, TValue>, TAllocator> >
	class sorted_vector : private vector<pair<TKey, TValue>, TAllocator, TStorage >
	{
            using Base = vector<pair<TKey, TValue>, TAllocator, TStorage>;
	public:
            using key_type = TKey;
            using mapped_type = TValue;
            using size_type = Base::size_type;
            using value_type =  Base::value_type;
            using iterator =  Base::iterator;
            using const_iterator = Base::const_iterator;
            using allocator_type = Base::allocator_type  ;

        explicit sorted_vector(const allocator_type& allocator = allocator_type())
        	: Base(allocator)
        {
        }
        template <class InputIterator> sorted_vector(InputIterator first, InputIterator last, 
                const allocator_type& allocator = allocator_type())
        	: Base(first, last, allocator)
        {
         	std::quick_sort(begin(), end(), m_compare);
         	assert(invariant());
        }
        using Base::begin;
        using Base::end;
        using Base::size;
        using Base::empty;
        using Base::capacity;

        pair<iterator, bool> insert(const value_type& val)
        {
            assert(invariant());
            bool found(true);
            iterator it = lower_bound(val.first);
            assert(it == end() || !m_compare(*it, val));
            if (it == end() || m_compare(*it, val))
            {
                it = Base::insert(it, val);
                found = false;
            }
            assert(invariant());
            return pair<iterator, bool>(it, !found);
        }
        inline  pair<iterator, bool> insert(const key_type& k, const mapped_type& v)
        {
         	return insert(value_type(k, v));
        }

        iterator find(const key_type& k)
		{
			assert(invariant());
		  	iterator i(lower_bound(k));
			if (i != end() && m_compare(k, *i))
			{
		     	i = end();
		   	}
			return i;
		}
    	const_iterator find(const key_type& k) const
    	{       
       		assert(invariant());
        	const_iterator i(lower_bound(k));
        	if (i != end() && m_compare(k, *i))
        	{
              	i = end();
          	}
        	return i;
        }

        inline iterator erase(iterator it)
        {
         	assert(invariant());
         	return Base::erase(it);
        }
        size_type erase(const key_type& k)
    	{
          	iterator i(find(k));
        	if (i == end()) 
               	return 0;
        	erase(i);
          	assert(invariant());
        	return 1;
        }

        using Base::clear;
        using Base::get_allocator;
        using Base::set_allocator;

        iterator lower_bound(const key_type& k)
        {
         	return std::lower_bound(begin(), end(), k, m_compare);
        }
        const_iterator lower_bound(const key_type& k) const
        {
          	return std::lower_bound(begin(), end(), k, m_compare);
        }
        iterator upper_bound(const key_type& k)
        {
          	return std::upper_bound(begin(), end(), k, m_compare);
        }
        const_iterator upper_bound(const key_type& k) const
        {
          	return std::upper_bound(begin(), end(), k, m_compare);
        }
	private:
        sorted_vector(const sorted_vector&);
        sorted_vector& operator=(const sorted_vector&);

        bool invariant() const
        {
            const_iterator first = begin();
            const_iterator last = end();
            assert(last >= first);
            if (first != last)
            {
                    const_iterator next = first;
                    if (++next != last)
                    {
                            assert(m_compare(*first, *next));
                            first = next;
                    }
            }
            return true;
        }
		internal::compare_func<value_type, TCompare>    m_compare;
	};
}
#endif


