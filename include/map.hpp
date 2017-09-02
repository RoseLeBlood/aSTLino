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
 * File:   map.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:50
 */

#ifndef STD_MAP_H
#define STD_MAP_H

#include "algorithm.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"

namespace std
{
	template<typename Tk, typename Tv, class TAllocator = std::allocator> class map 
	{
	    template<typename TNodePtr, typename TPtr, typename TRef> class node_iterator
	    {
	    public:
	        using iterator_category = forward_iterator_tag;

	        explicit node_iterator(TNodePtr node, const map* map_)
	        	: m_node(node), m_map(map_)
	        {
	        }
	        template<typename UNodePtr, typename UPtr, typename URef>
	        node_iterator(const node_iterator<UNodePtr, UPtr, URef>& rhs)
	        	: m_node(rhs.node()), m_map(rhs.get_map())
	        {
	       
	        }

	        TRef operator*() const
	        {
	            assert(m_node != 0);
	            return m_node->value;
	        }
	        TPtr operator->() const
	        {
	         	return &m_node->value;
	        }
	        TNodePtr node() const
	        {
	        	return m_node;
	        }

	        node_iterator& operator++() 
	        {
	            assert(m_node != 0);
	            TNodePtr next = find_next_node(m_node);
	            m_node = next;
	            return *this;
	        } 
	        node_iterator operator++(int)
	        {
	            node_iterator copy(*this);
	            ++(*this);
	            return copy;
	        }

	        bool operator==(const node_iterator& rhs) const
	        {
	        	return rhs.m_node == m_node && m_map == rhs.m_map;
	        }
	        bool operator!=(const node_iterator& rhs) const
	        {
	       		return !(rhs == *this);
	        }

	        const map* get_map() const 
	        { 
	        	return m_map; 
	        }
	    private:
	        TNodePtr find_next_node(TNodePtr node) const
	        {
	         	return m_map->m_tree.find_next_node(node);
	        }

	        TNodePtr        m_node;
	        const map*      m_map;
		};
	    template<typename Tkm, typename Tvm> struct map_pair : public std::pair<Tkm, Tvm>
	    {
	        map_pair() 
	        {
	        }
	        map_pair(const Tkm& k, const Tvm& v): pair<Tkm, Tvm>(k, v) 
	        {
	        }
	        bool operator<(const map_pair& rhs) const
	        {
	        	return std::pair<Tkm, Tvm>::first < rhs.first;
	        }
	        inline const Tkm& get_key() const      
	        { 
	        	return std::pair<Tkm, Tvm>::first; 
	        }
	    };
	    template<typename Tkm, typename Tvm> struct map_traits
	    {
	        using key_type = Tkm;
	        using value_type = map_pair<Tkm, Tvm>;
	    };
	public:
	    using key_type = Tk;
	    using data_type = Tv;
	    using value_type = map_pair<Tk, Tv>;
	    using tree_type = rb_tree_base<map_traits<Tk, Tv> >;
	    using size_type = tree_type::size_type;
	    using iterator = node_iterator<typename tree_type::node*, value_type*, value_type&>;
	    using const_iterator = node_iterator<typename tree_type::node*, const value_type*, const value_type&>;
	    using allocator_type = TAllocator;

	    explicit map(const allocator_type& allocator = allocator_type())
	    	:  m_tree(allocator) 
	    {
	 
	    }
	    template<typename TInputIterator>
	    map(TInputIterator dataBegin, TInputIterator dataEnd, const allocator_type& allocator = allocator_type())
	    	: m_tree(allocator)
	    {
            TInputIterator it = dataBegin;
            while (it != dataEnd)
            {
                insert(*it);
                ++it;
            }
	    }

	    iterator begin()                                
	    { 
	    	return iterator(m_tree.get_begin_node(), this); 
	    }
	    const_iterator begin() const    
	    { 
	    	return const_iterator(m_tree.get_begin_node(), this); 
	    }
	    iterator end()                                  
	    { 
	    	return iterator(0, this); 
	    }
	    const_iterator end() const              
	    { 
	    	return const_iterator(0, this); 
	    }

	   
	    data_type& operator[](const key_type& key)
	    {
            typename tree_type::node* n = m_tree.find_node(key);
            if (n == 0)
             	n = m_tree.insert(value_type(key, Tv()));
            return n->value.second;
	    }
	    inline iterator insert(const value_type& v)
	    {
            typename tree_type::node* n = m_tree.insert(v);
	      	return iterator(n, this);
	    }
	    inline iterator find(const key_type& key)
	    {
	       	return iterator(m_tree.find_node(key), this);
	    }
	    inline size_type erase(const key_type& key)
	    {
	       	return m_tree.erase(key);
	    }
	    inline void clear() { m_tree.clear(); }
	    inline void swap(map& other)
	    {
	       	m_tree.swap(other.m_tree);
	    }

	    inline bool empty() const              
	    { 
	    	return m_tree.empty();
	    }
	    inline size_type size() const  
	    { 
	    	return m_tree.size();
	    }
	private:
	    tree_type       m_tree;
	};
}

#endif 


