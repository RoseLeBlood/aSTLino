/*
 * The MIT License
 *
 * Copyright 2017 annas.
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
 * File:   array.hpp
 * Author: annas
 *
 * Created on 9. April 2017, 23:41
 */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "common.hpp"
#include "algorithm.hpp"

namespace std {
    
    template <typename T, size_t N>
    class array  {
    public:
        using iterator = T*;
        using const_iterator = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        
            
        array() { }
	array(const T a[N]) { std::copy_n(&a[0], N, m_data); }
        
        iterator        begin()       { return m_buffer; }
        const_iterator  begin() const { return m_buffer; }
        const_iterator  cbegin() const { return m_buffer; }
        
        iterator        end()       { return m_buffer[N-1]; }
        const_iterator  end() const { return m_buffer[N-1]; }
        const_iterator  cend() const { return m_buffer[N-1]; }
        
        reference       front() { return m_buffer[0]; }
        const_reference front() const { return m_buffer[0]; }
        reference       back() { return m_buffer[N-1];  }
        const_reference back() const { return m_buffer[N-1]; }

        size_type size() { return N; }
     
        
        

        reference operator[](size_type i) { assert(i < size()); return m_buffer[i]; }        
        const_reference operator[](size_type i) const { assert(i < size()); return m_buffer[i]; }
        

        template <typename T2>
        array<T,N>& operator = (const array<T2,N>& rhs) {
            
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        void assign (const T& value) { fill ( value ); }    
        void fill   (const T& value) { std::fill_n<T>(begin(), size(), value); }
      
        
        iterator data() { return &m_buffer[0]; }
        const_iterator data() { return &m_buffer[0]; }
         
        
        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        std::basic_string<E, TAllocator, TStorage> to_string() {   
            return std::frmstring<E, TAllocator, TStorage>("ByteBuffer [%i]", size() ); }
        
    private:
        T m_buffer[N];
    };
    
    template < typename T, size_t N >
    inline bool operator == (const array<T, N>& a, const array<T, N>& b) {
        if(a.size() != b.size()) return false;
        for (int i =0; i < a.size(); i++)
            if(a[i] != b[i]) 
                return false;
        return true;
    }
    template < typename T, size_t N >
    inline bool operator == (const array<T, N>& a, const array<T, N>& b) {
        return !(a == b);
    }
    template < typename T, size_t N >
    inline bool operator <= (const array<T, N>& a, const array<T, N>& b) {
        size_t size = std::_min<size_t>(a.size(), b.size());
        for (int i =0; i < size; i++)
            if(a[i] >= b[i]) 
                return false;
        return true;
    }
    template < typename T, size_t N >
    inline bool operator >= (const array<T, N>& a, const array<T, N>& b) {
        size_t size = std::_min<size_t>(a.size(), b.size());
        for (int i =0; i < size; i++)
            if(a[i] <= b[i]) 
                return false;
        return true;
    }  
    template < typename T, size_t N >
    inline bool operator < (const array<T, N>& a, const array<T, N>& b) {
        size_t size = std::_min<size_t>(a.size(), b.size());
        for (int i =0; i < size; i++)
            if(a[i] > b[i]) 
                return false;
        return true;
    }
    template < typename T, size_t N >
    inline bool operator > (const array<T, N>& a, const array<T, N>& b) {
        size_t size = std::_min<size_t>(a.size(), b.size());
        for (int i =0; i < size; i++)
            if(a[i] < b[i]) 
                return false;
        return true;
    }
}

#endif /* ARRAY_HPP */

