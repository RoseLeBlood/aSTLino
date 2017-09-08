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
 * File:   intrusive_list.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:46
 */

#ifndef STD_INTRUSIVE_LIST_H
#define STD_INTRUSIVE_LIST_H

#include "iterator.hpp"
#include "type_traits.hpp"

namespace std
{
	struct intrusive_list_node
	{
            intrusive_list_node()
            {
                    next = prev = this;
            }
            bool in_list() const    { return this != next; }

            intrusive_list_node*    next;
            intrusive_list_node*    prev;
	};

	template<typename Pointer, typename Reference> class intrusive_list_iterator
	{
	public:
	    using pointer = Pointer;
	    using reference = Reference;
	    using iterator_category = bidirectional_iterator_tag;

            intrusive_list_iterator()
                    : m_node(0) 
            {
            }
            explicit intrusive_list_iterator(Pointer iterNode)
                    : m_node(iterNode)
            {
            }

            Reference operator*() const
            {
                assert(m_node);
                return *m_node;
            }
            Pointer operator->() const
            {
                return m_node;
            }
            Pointer node() const
            {
                return m_node;
            }

            intrusive_list_iterator& operator++()
            {
                m_node = static_cast<Pointer>(m_node->next);
                return *this;
            }
            intrusive_list_iterator& operator--()
            {
                m_node = static_cast<Pointer>(m_node->prev);
                return *this;
            }
            intrusive_list_iterator operator++(int)
            {
                intrusive_list_iterator copy(*this);
                ++(*this);
                return copy;
            }
            intrusive_list_iterator operator--(int)
            {
                intrusive_list_iterator copy(*this);
                --(*this);
                return copy;
            }
            bool operator==(const intrusive_list_iterator& rhs) const
            {
                return rhs.m_node == m_node;
            }
            bool operator!=(const intrusive_list_iterator& rhs) const
            {
                return !(rhs == *this);
            }
            private:
                    Pointer m_node;
	};


	class intrusive_list_base
	{
	public:
	    using size_type = int;

	    void pop_back()
	    {
	            unlink(m_root.prev);
	    }
	    void pop_front()
	    {
	            unlink(m_root.next);
	    }

	    size_type size() const {
              	size_type numNodes(0);
        	const intrusive_list_node* iter = &m_root;
              	do
        	{
            		iter = iter->next;
            		++numNodes;
        	} while (iter != &m_root);
        	return numNodes - 1;
            }
	    bool empty() const      
	    { 
	    	return !m_root.in_list(); 
	    }
	protected:
            intrusive_list_base() : m_root() { }
            ~intrusive_list_base() {}

            static void link(intrusive_list_node* node, intrusive_list_node* nextNode) {
		assert(!node->in_list());
        	node->prev = nextNode->prev;
        	node->prev->next = node;
        	nextNode->prev = node;
        	node->next = nextNode;
            }
            static void unlink(intrusive_list_node* node) {
		assert(node->in_list());
        	node->prev->next = node->next;
        	node->next->prev = node->prev;
        	node->next = node->prev = node;
            }
            protected:
                    intrusive_list_node     m_root;
        private:
            intrusive_list_base(const intrusive_list_base&);
            intrusive_list_base& operator=(const intrusive_list_base&);
        };

            template<class T> class intrusive_list : public intrusive_list_base
            {
            public:
                using node_type = T;
                using value_type = T;
                using iterator = intrusive_list_iterator<T*, T&>;
                using const_iterator = intrusive_list_iterator<const T*, const T&>;

                intrusive_list() : intrusive_list_base()
                {
                    intrusive_list_node* testNode((T*)0);
                    static_cast<void>(sizeof(testNode));
                }

                void push_back(value_type* v)
                {               
                        link(v, &m_root);
                }
                void push_front(value_type* v)
                {
                    link(v, m_root.next);
                }

                iterator begin()                                
                { 
                        return iterator(upcast(m_root.next)); 
                }
                const_iterator begin() const   
                {
                        return const_iterator(upcast(m_root.next)); 
                }
                iterator end()                                  
                { 
                        return iterator(upcast(&m_root)); 
                }
                const_iterator end() const              
                { 
                        return const_iterator(upcast(&m_root)); 
                }
                value_type* front()                     
                { 
                        return upcast(m_root.next); 
                }
                const value_type* front() const 
                { 
                        return upcast(m_root.next); 
                }
                value_type* back()                              
                { 
                        return upcast(m_root.prev); 
                }
                const value_type* back() const  
                { 
                        return upcast(m_root.prev); 
                }

                iterator insert(iterator pos, value_type* v)
                {
                    link(v, pos.node());
                    return iterator(v);
                }
                iterator erase(iterator it)
                {
                    iterator itErase(it);
                    ++it;
                    unlink(itErase.node());
                    return it;
                }
                iterator erase(iterator first, iterator last)
                {
                    while (first != last)
                            first = erase(first);
                    return first;
                }

                void clear()
                {
                        erase(begin(), end());
                }
                static void remove(value_type* v)
                {
                        unlink(v);
                }
            private:
                static inline node_type* upcast(intrusive_list_node* n)
                {
                        return static_cast<node_type*>(n);
                }
                static inline const node_type* upcast(const intrusive_list_node* n)
                {
                        return static_cast<const node_type*>(n);
                }
            };
} 
#endif 


