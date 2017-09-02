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
 * File:   tree.hpp
 * Author: annas
 *
 * Created on 11. November 2016, 15:20
 */

#ifndef _STD_TREE_HPP_
#define _STD_TREE_HPP_

#include "common.hpp"
#include "string.hpp"

namespace std
{
    
    template < typename T, typename I = std::string>
    class node_ptr
    {
    public:
        using name_type = I;
        using value_type = T;
        using self_type = node_ptr<T,I>;
        
        explicit node(name_type strName, value_type* data, self_type* pParent ) {
            m_index = strName;
            m_pParent = pParent;
            m_pChild = NULL;
	    m_pSibling = NULL;
	    m_data = data;
        }
	~node();

	self_type* add_child(self_type* pChild) {
            if(! m_pChild) { //erstes Kind
		m_pChild = pChild;
                m_pChild->m_pParent = this;
            }
	    else
		return m_pChild->add_child(pChild);
            return m_pChild;
	
        }
	self_type* add_sibling(self_type* pSibling) {
            if(!m_pSibling) {//Erstes Geschwister {
		m_pSibling = pSibling;
                m_pSibling->m_pParent = this->m_pParent;
            }
	    else            //Probieren wir's bei den Geschwistern
		return m_pSibling->add_sibling(pSibling);
            return m_pSibling;
        }

	self_type*  find(name_type index) {
            if(m_index == index)
                return this;
            if(m_pSibling) {
		self_type* praNode = m_pSibling->find(index);
		if(praNode) return praNode;
	    }
            //Kinder
	    if(m_pChild) {
		self_type* praNode = m_pChild->find(index);
		if(praNode) return praNode;
	    }
            return 0;	
        }
	self_type*  root() {
            if(m_pParent) return m_pParent->root();
	    return this;
        }

        value_type& get() {
            return *m_data;
        }
    private:
        name_type* m_index;
        self_type* m_pChild, m_pSibling, m_pParent; 
        value_type* m_data;
    };
}

#endif /* TREE_HPP */

