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
 * File:   vector2.hpp
 * Author: annas
 *
 * Created on 11. November 2016, 01:28
 */

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <math.h>
#include "../algorithm.hpp"
#include "../common.hpp"
#include "../unknown.hpp"
#include "../string.hpp"

namespace std 
{
    namespace math
    {
        template < typename T> 
        class vector2;
        
        using vec2f = vector2<float>  ;
        using vec2d = vector2<double>;
        
        
        template < typename T >
        class vector2 :  public object
        {
        public:
            using value_type = T;
            using self_type = vector2<T> ;
            using pointer = T* ;
                
            union
	    {
		struct
		{
		    value_type x;
		    value_type y;
		};
		value_type c[2];
	    };
            
                
                
            vector2() 														{}
	    vector2(value_type _x, value_type _y) : x(_x), y(_y)	{}
	    vector2(value_type _f) : x(_f), y(_f)			{}
            vector2(const vector2& vec) : x(vec.x), y(vec.y)	{}
            vector2(const pointer lpvec) : x(lpvec[0]), y(lpvec[1])	{}

            operator pointer ()		{ return (pointer)(c); }
            operator void* ()		{ return (void*)(c); }
                
            self_type& operator =  (const self_type& v)	{ 
                x = v.x; y = v.y; return *this; }
            self_type& operator += (const self_type& v)	{
                x += v.x; y += v.y; return *this; }
            self_type& operator -= (const self_type& v) { 
                x -= v.x; y -= v.y; return *this; }
            self_type& operator *= (const self_type& v) { 
                x *= v.x; y *= v.y; return *this; }
            self_type& operator /= (const self_type& v)	{ 
                x /= v.x; y /= v.y; return *this; }

            self_type& operator /= (const value_type& f)	{ 
                x /= f; y /= f; return *this; }
            self_type& operator *= (const value_type& f)	{ 
                x *= f; y *= f; return *this; }
            
            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                char xs[10], ys[10], buffer[32];
                dtostrf(x,4,2,xs); dtostrf(y,4,2,ys);
                int len = sprintf(buffer, "(%s %s)", xs, ys);
                return std::basic_string<E, TAllocator, TStorage>(buffer, len);
	    }
	};
        
        template < typename T >
        inline vector2<T> operator + (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x + b.x, a.y + b.y); }
	template < typename T >
        inline vector2<T> operator - (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x - b.x, a.y - b.y); }
	template < typename T >
        inline vector2<T> operator * (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x * b.x, a.y * b.y); }
	template < typename T >
        inline vector2<T> operator / (const vector2<T>& a, const vector2<T>& b)
            { return vector2<T>(a.x / b.x, a.y / b.y); }
	template < typename T >
        inline vector2<T> operator + (const float& f, const vector2<T>& b)		
            { return vector2<T>(f + b.x, f + b.y); }
	template < typename T >
        inline vector2<T> operator - (const float& f, const vector2<T>& b)		
            { return vector2<T>(f - b.x, f - b.y); }
	template < typename T >
        inline vector2<T> operator * (const float& f, const vector2<T>& b)		
            { return vector2<T>(f * b.x, f * b.y); }
	template < typename T >
        inline vector2<T> operator / (const float& f, const vector2<T>& b)		
            { return vector2<T>(f / b.x, f / b.y); }
	template < typename T >
        inline vector2<T> operator - (const vector2<T>& a, const float& f)		
            { return vector2<T>(a.x - f, a.y - f); }
	template < typename T >
        inline vector2<T> operator / (const vector2<T>& a, const float& f)		
            { return vector2<T>(a.x / f, a.y / f); }

        template < typename T >
	inline bool operator == (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x == b.x) && (a.y == b.y)); }
        template < typename T >
        inline bool operator != (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x != b.x) && (a.y != b.y)); }
	template < typename T >
        inline bool operator <= (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x <= b.x) && (a.y <= b.y)); }
	template < typename T >
        inline bool operator >= (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x >= b.x) && (a.y >= b.y)); }
	template < typename T >
        inline bool operator <  (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x < b.x) && (a.y < b.x)); }
	template < typename T >
        inline bool operator >  (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x > b.x) && (a.y > b.y)); }
        
        template < typename T >
        inline T	 lenght(const  vector2<T>& v)									
            { return (T)(v.x * v.x + v.y * v.y ); }
	template < typename T >
        inline T	 lenghtSq(const vector2<T>& v)									
            { return (T)sqrt(v.x * v.x + v.y * v.y ); }
	template < typename T >
        inline vector2<T> normalize(const vector2<T>& v)									
            { return v / (T)sqrt(v.x * v.x + v.y * v.y ); }
	template < typename T >
        inline vector2<T> normalizeEx(const vector2<T>& v)								
            { return v / (T)sqrt((v.x * v.x + v.y * v.y ) + 0.0001f); }

        template < typename T >
	inline T dot(const vector2<T>& v1, const vector2<T>& v2)					
            { return (T)(v1.x * v2.x + v1.y * v2.y);}
        template < typename T >
	inline T angle(const vector2<T>& v1, const vector2<T>& v2)				
            { return (T)acos((v1.x * v2.x + v1.y * v2.y ) /
	             (T)sqrt((v1.x * v1.x + v1.y * v1.y ) * (v2.x * v2.x + v2.y * v2.y))); }
        template < typename T >
	inline vector2<T> interpolate_coords(const vector2<T>& v1, const vector2<T>& v2, const T p)								
            { return v1 + p * (v2 - v1); }
        template < typename T >
	inline vector2<T> interpolate_normal(const vector2<T>& v1, const vector2<T>& v2, const T p)								
            { return normalize(v1 + p * (v2 - v1)); }
        template < typename T >
	inline bool nearEqual(const vector2<T>& v1, vector2<T>& v2, const vector2<T>& epsilon)							
            { return (( abs((T)(v1.x - v2.x )) <= epsilon) && (abs((T)(v1.y - v2.y)) <= epsilon)); }

        template <typename T>
        inline vector2<T> _min(const vector2<T>& c1, const vector2<T>& c2)
            {return vector2<T>(std::_min<T>(c1.x, c2.x), std::_min<T>(c1.y, c2.y));}
	template <typename T>
        inline vector2<T> _max(const vector2<T>& c1, const vector2<T>& c2)
            {return vector2<T>(std::_max<T>(c1.x, c2.x), std::_max<T>(c1.y, c2.y));}
        template <typename T>
        inline vector2<T> scale(const vector2<T>& v, const float s)
            {return vector2<T>(v.x * s, v.y*s);}
        
    }
    template<typename T, typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
    inline std::basic_string<E, TAllocator, TStorage> vec2_string(const std::math::vector2<T>& v, flags_t f = flags_t::dec  ) {   
            return v.to_string<E, TAllocator, TStorage>(); }


        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec2_string(const std::math::vec2f& v, flags_t f = flags_t::dec  ) {   
            return std::vec2_string<float, E, TAllocator, TStorage>(v); }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec2_string(const std::math::vec2d& v, flags_t f = flags_t::dec  ) {   
            return std::vec2_string<double, E, TAllocator, TStorage>(v); }

    
    
    
}

#endif /* VECTOR2_HPP */

