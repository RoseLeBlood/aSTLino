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
 * File:   fixed_list.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 01:30
 */

#ifndef _STD_FIXED_LIST_H_
#define _STD_FIXED_LIST_H_

#include "algorithm.hpp"
#include "inttokey.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace std
{
    template<typename T, size_t TCapacity> 
    class fixed_list
    {
        template<int i> struct type_selector {
            typedef unsigned char   index_type;
	};
	struct type_selector<1> {
	  typedef unsigned short  index_type;
	};
	struct type_selector<2> {
	    typedef unsigned long   index_type;
	};

	enum { 
	    select = TCapacity+1 > 255 ? (TCapacity+1 > 65535 ? 2 : 1) : 0 
	};
        using index_type_selector = type_selector<select> ;

    public:
        using index_type = index_type_selector::index_type;

    private:
	struct node {
	    node() { }
	    explicit node(const T& v, int i)
	        : value(v), index((index_type)i) { }
	    void reset()
                { index = index_next = index_prev = 0; }
	    bool in_list() const 
                { return index != index_next; }

	    T               value;
	    index_type      index;
	    index_type      index_next;
	    index_type      index_prev;
	};
        template<typename TNodePtr, typename TPtr, typename TRef> 
        class node_iterator 
        {
        public:
            using   iterator_category = bidirectional_iterator_tag;
            explicit node_iterator(TNodePtr node, const fixed_list* list)
		: m_node(node), m_list(list) { }
            template<typename UNodePtr, typename UPtr, typename URef>
            node_iterator(const node_iterator<UNodePtr, UPtr, URef>& rhs)
                : m_node(rhs.node()), m_list(rhs.list()) { }

            TRef operator*() const {
	        assert(m_node != 0);
	        return m_node->value;
            }
            TPtr operator->() const 
                { return &m_node->value; }
	    TNodePtr node() const
                { return m_node; }
            const fixed_list* list() const
		{ return m_list; }
            node_iterator& operator++() {
	        m_node = m_list->get_next(m_node);
	        return *this;
            }
            node_iterator& operator--() {
	        m_node = m_list->get_prev(m_node);
	        return *this;
            }
            node_iterator operator++(int) {
	        node_iterator copy(*this);
	        ++(*this);
	        return copy;
            }
            node_iterator operator--(int) {
	        node_iterator copy(*this);
	        --(*this);
	        return copy;
            }
            bool operator==(const node_iterator& rhs) const
		{ return rhs.m_node == m_node; }
            bool operator!=(const node_iterator& rhs) const
                { return !(rhs == *this); }

        private:
            TNodePtr            	m_node;
            const fixed_list*       m_list;
        };
    public:
        using value_type = T;
	using size_type = int;
        using iterator = node_iterator<node*, T*, T&>;
	using const_iterator = node_iterator<const node*, const T*, const T&>;

	fixed_list() : m_num_nodes(0) {
            init_free_indices();
            get_root()->reset();
	}
	template<class InputIterator>
        fixed_list(InputIterator first, InputIterator last) {
            get_root()->reset();
            assign(first, last);
	}
	fixed_list(const fixed_list& rhs) {
            get_root()->reset();
            copy(rhs, int_to_type<has_trivial_copy<T>::value>());
	}
	explicit fixed_list(e_noinitialize) {
	    }
            
	~fixed_list() {
            clear();
	}

	fixed_list& operator=(const fixed_list& rhs) {
            if (this != &rhs) {
                copy(rhs, int_to_type<has_trivial_copy<T>::value>());
            }
            return *this;
	}

	iterator begin()                                
            { return iterator(get_next(get_root()), this); }
	const_iterator begin() const    
            { return const_iterator(get_next(get_root()), this); }
	iterator end()                                  
            { return iterator(get_root(), this); }
	const_iterator end() const              
            { return const_iterator(get_root(), this); }
	const T& front() const  
            { assert(!empty()); return get_next(get_root())->value; }
	T& front()                              
            { assert(!empty()); return get_next(get_root())->value; }
	const T& back() const   
            { assert(!empty()); return get_prev(get_root())->value; }
	T& back() 
            { assert(!empty()); return get_prev(get_root())->value; }

	void push_front(const T& value) {
            assert(m_free_index_top > 0);       // 0 is root
            const int index = m_free_indices[m_free_index_top--];
            node* new_node = construct_node(value, index);
            ++m_num_nodes;
            assert(m_num_nodes <= TCapacity);
            link_before(new_node, get_next(get_root()));
	}
	inline void pop_front() {
            assert(!empty());
            node* front_node = get_next(get_root());
            m_free_indices[++m_free_index_top] = front_node->index;
            unlink(front_node);
            destruct_node(front_node);
            --m_num_nodes;
	}
	void push_back(const T& value) {
            assert(m_free_index_top > 0);       // 0 is root
            const int index = m_free_indices[m_free_index_top--];
            node* new_node = construct_node(value, index);
            ++m_num_nodes;
            assert(m_num_nodes <= TCapacity + 1);
            link_before(new_node, get_root());
	}
	inline void pop_back() {
            assert(!empty());
            node* back_node = get_prev(get_root());
            m_free_indices[++m_free_index_top] = back_node->index;
            unlink(back_node);
            destruct_node(back_node);
            --m_num_nodes;
	}

	iterator insert(iterator pos, const T& value) {
            assert(m_free_index_top > 0);
            const int index = m_free_indices[m_free_index_top--];
            node* new_node = construct_node(value, index);
            link_before(new_node, pos.node());
            ++m_num_nodes;
            return iterator(new_node, this);
	}
	iterator erase(iterator it) {
            assert(!empty());
            assert(it.node()->in_list());
            assert(it.list() == this);
            iterator it_erase(it);
            ++it;
            node* erase_node = it_erase.node();
            m_free_indices[++m_free_index_top] = erase_node->index;
            unlink(erase_node);
            destruct_node(erase_node);
            --m_num_nodes;
            return it;
	}
	iterator erase(iterator first, iterator last) {
            while (first != last)
                first = erase(first);
            return first;
	}

	template<class InputIterator> 
        void assign(InputIterator first, InputIterator last) {
            clear();
            while (first != last) {
                push_back(*first);
                ++first;
            }
	}
	void clear() {
            node* root = get_root();
            node* iter = get_next(root);
            while (iter != root) {
                node* next = get_next(iter);
                destruct_node(iter);
                iter = next;
            }
            root->reset();
            m_num_nodes = 0;
            init_free_indices();
	}

	bool empty() const      
            { return m_num_nodes == 0; }
	size_type size() const
            { return m_num_nodes; }
    private:
	void link_before(node* n, node* next) {
            n->index_prev = next->index_prev;
            get_prev(n)->index_next = n->index;
            next->index_prev = n->index;
            n->index_next = next->index;
	}
	void unlink(node* n) {
            get_prev(n)->index_next = n->index_next;
            get_next(n)->index_prev = n->index_prev;
            n->index_next = n->index_prev = n->index;
	}
	inline node* get_prev(const node* n) const
            { return get_nodes() + n->index_prev; }
	inline node* get_next(const node* n) const
            { return get_nodes() + n->index_next; }

	node* construct_node(const T& value, int index) {
            node* mem = get_nodes() + index;
            return new (mem) node(value, index);
	}
	void destruct_node(node* n) {
            n->~node();
	}
	void init_free_indices() {
            for (int i = 0; i < TCapacity + 1; ++i)
                    m_free_indices[i] = (index_type)i;
            m_free_index_top = TCapacity;
        }
	inline node* get_nodes() const
	    { return (node*)(&m_node_mem[0]); }
	void copy(const fixed_list& rhs, int_to_type<true>)
	    { Sys::MemCpy(this, &rhs, sizeof(rhs)); }
	void copy(const fixed_list& rhs, int_to_type<false>)
	    { assign(rhs.begin(), rhs.end()); }
	inline node* get_root() const
            { return (node*)(&m_node_mem[0]); }

        using etype_t =  aligned_as<node>::res;

	etype_t                 m_node_mem[sizeof(node) * (TCapacity + 1) / sizeof(etype_t)];
	index_type              m_free_indices[TCapacity + 1];
	int                     m_free_index_top;
	size_type               m_num_nodes;    // Excluding root!
    };
}

#endif


