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
 * File:   exp_vector.hpp
 * Author: annas
 *
 * Created on 18. April 2017, 19:07
 */

#ifndef EXP_VECTOR_HPP
#define EXP_VECTOR_HPP

#include "vector.hpp"
#include "config.h"

namespace std {
  
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator + (const vector<T, TAllocator, TStorage>& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif
        for(int i = 0; i < size; i++)
            c.push_back(a[i] + b[i]);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator + (const vector<T, TAllocator, TStorage>& a, 
                                                       const T& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif       
        for(int i = 0; i < size; i++)
            c.push_back(a[i] + b);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator + (const T& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : b.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a + b[i]);
        return c;    
    }
    //sub ------
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator - (const vector<T, TAllocator, TStorage>& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] - b[i]);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator - (const vector<T, TAllocator, TStorage>& a) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(-a[i]);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator - (const vector<T, TAllocator, TStorage>& a, 
                                                const T& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] - b);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator - (const T& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : b.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a - b[i]);
        return c;    
    }
    //mul ----
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator * (const vector<T, TAllocator, TStorage>& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] * b[i]);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator * (const vector<T, TAllocator, TStorage>& a, 
                                                const T& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] * b);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator * (const T& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : b.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a * b[i]);
        return c;    
    }
    // div -----
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator / (const vector<T, TAllocator, TStorage>& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] / b[i]);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator / (const vector<T, TAllocator, TStorage>& a, 
                                                const T& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : a.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a[i] / b);
        return c;    
    }
    template<typename T, int calc = 0, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> operator / (const T& a, 
                                                const vector<T, TAllocator, TStorage>& b) {
        vector<T, TAllocator, TStorage> c = vector<T, TAllocator, TStorage>();
        int size = (calc != 0 ? calc : b.size());
#ifdef ASSTL_USE_OPENMP
    #pragma omp parallel for
#endif        
        for(int i = 0; i < size; i++)
            c.push_back(a / b[i]);
        return c;    
    }
    // scale ----
    template<typename T, class TAllocator = std::allocator, class TStorage = standard_vector_storage<T, TAllocator> >
    inline vector<T, TAllocator, TStorage> scale(const vector<T, TAllocator, TStorage>& v,
                                                 const T s) {
        return v * s;        
    }
    
}


#endif /* EXP_VECTOR_HPP */

