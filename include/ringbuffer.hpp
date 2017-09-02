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
 * File:   ringbuffer.hpp
 * Author: annas
 *
 * Created on 10. November 2016, 23:09
 */

#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include "mutex.hpp"
#include "common.hpp"
#include "allocator.hpp"
namespace std
{
    template<typename T, typename E = typename T::value_type>
    class ring_buffer_iterator 
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t; 
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using self_type = ring_buffer_iterator<T>;
        
        ring_buffer_iterator(pointer b, size_t start_pos)
            : m_buf(b), m_pos(start_pos) { }
        ring_buffer_iterator(const ring_buffer_iterator& it)
            : m_buf(it.m_buf), m_pos(it.m_pos) { }
        
        ring_buffer_iterator& operator = (const ring_buffer_iterator& it) {
              m_buf = it.m_buf; m_pos = it.m_pos; return *this;
        }
      
        E &operator*() {
            return (*m_buf)[m_pos]; 
        }
        E *operator->() { 
            return &(operator*()); 
        }
        self_type &operator++() {
             ++m_pos;
             return *this;
        }
        self_type &operator--() {
             --m_pos;
             return *this;
        }
        self_type operator ++ (int) {
            self_type tmp(*this);
            ++(*this);
            return tmp;
        }
        self_type operator -- (int) {
            self_type tmp(*this);
            --(*this);
            return tmp;
        }
        self_type operator + (difference_type n) {
            self_type tmp(*this);
            tmp.m_pos += n;
            return tmp;
        }
        self_type operator - (difference_type n) {
            self_type tmp(*this);
            tmp.m_pos -= n;
            return tmp;
        }
        self_type &operator += (difference_type n) {
            m_pos += n;
            return *this;
        }
        self_type &operator -= (difference_type n) {
            m_pos -= n;
            return *this;
        }
        bool operator == (const self_type &other) const {
            return (this->m_pos == other.m_pos);
        }
        bool operator != (const self_type &other) const {
             return (this->m_pos != other.m_pos);
        }
        value_type& operator [] (difference_type n) const {
            return *(*this + n); 
        }
        bool operator < (const self_type& it) const {
                  return m_pos < it.m_pos;
        }
        bool operator > (const self_type& it) const {
            return   it < *this;  
        }
        bool operator <= (const self_type& it) const { 
            return !(it < *this); 
        }
        bool operator >= (const self_type& it) const { 
            return !(*this < it); 
        }
    private:
        value_type *m_buf;
        size_t     m_pos;  
    };
    template <class T, class TAllocator = std::allocator>
    class ring_buffer
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        using difference_type = ptrdiff_t; 
        using allocator_type = TAllocator;
        
        using iterator = ring_buffer_iterator<ring_buffer<T, TAllocator>, value_type> ; 
        using const_iterator = ring_buffer_iterator<ring_buffer<T, TAllocator>, const value_type>;

        explicit ring_buffer(size_t capacity = 100)
                : m_Array(new T[capacity]),
                  m_ArraySize(capacity),
                  m_Head(0), m_Tail(0),
                  m_ContentsSize(0) {}
                
        ~ring_buffer() { delete [] m_Array; }
    
        
        void clear()  { 
            m_Head = m_Tail = m_ContentsSize = 0; 
        }
        
        void push_back(const value_type &item) {
            inc_tail();
            if (m_ContentsSize == m_ArraySize)
                inc_head();
            m_Array[m_Tail] = item;
        }
        reference pop_front() { 
            inc_head(); 
            return front();
        }
        const_reference pop_front() const { 
            inc_head(); 
            return front();
        }
        iterator begin() { 
            return iterator(this, empty() ? 0 : front()); 
        }
        iterator end() { 
            return iterator(this, size()); 
        }
        const_iterator begin() { 
            return const_iterator(this, 0); 
        }
        const_iterator end() { 
            return const_iterator(this, size()); 
        }
        reference       front()       { 
            return m_Array[m_Head];
        }
        const_reference front() const { 
            return m_Array[m_Head]; 
        }
        const_reference back() const  { 
            return m_Array[m_Tail]; 
        }
        reference       back()        { 
            return m_Array[m_Tail]; 
        }
        
        size_type size() const {
            return m_ArraySize;
        }
        size_type capacity() const {
            return m_ContentsSize;
        }
        bool empty() const {
            return size() == 0; 
        }
        bool full() const {
            return size() == capacity();
        }
        size_type max() const {
            return size_type(-1) / sizeof(value_type);
        }
    private:
        void inc_tail() {
            ++m_Tail;
            ++m_ContentsSize;
            if (m_Tail == m_ArraySize) 
                m_Tail = 0;
        }
        void inc_head() {
            ++m_Head;
            -m_ContentsSize;
            if (m_Head == m_ArraySize)
                m_Head = 0;
        }
    private:
        T      *m_Array;
        size_t  m_ArraySize;
        size_t  m_Head;
        size_t  m_Tail;
        size_t  m_ContentsSize;

    };
}

#endif /* RINGBUFFER_HPP */

