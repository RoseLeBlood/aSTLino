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
 * File:   vector3.hpp
 * Author: annas
 *
 * Created on 12. November 2016, 21:34
 */

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "../unknown.hpp"
#include "vector2.hpp"

namespace std
{
    namespace math
    {
        template < typename T > class vector3;
        typedef vector3<float>  vec3f;
        typedef vector3<double> vec3d;
        
        
        template < typename T >
        class vector3 : public object
        {
        public:
            typedef T value_type;
            typedef vector3<T> self_type;
            typedef T* pointer;
            
            union
	    {
		struct
		{
		    value_type x;
		    value_type y;
                    value_type z;
		};
		value_type c[3];
	    };
            vector3() 														{}
	    vector3(value_type _x, value_type _y, value_type _z) : x(_x), y(_y), z(_z)	{}
	    vector3(value_type _f) : x(_f), y(_f), z(_f)			{}
            vector3(const self_type& vec) : x(vec.x), y(vec.y), z(vec.z)	{}
            vector3(const vector2<T>& vec) : x(vec.x), y(vec.y), z(0)	{}
            vector3(const pointer lpvec) : x(lpvec[0]), y(lpvec[1]), z(lpvec(2))	{}

            operator pointer ()		{ return (pointer)(c); }
            operator void* ()		{ return (void*)(c); }
                
            self_type& operator =  (const self_type& v)	{ 
                x = v.x; y = v.y; z = v.z; return *this; } 
            self_type& operator = (const vector2<T>& v)     {
                x = v.x; y = v.y; z = 0; return *this; }
            self_type& operator += (const self_type& v)	{
                x += v.x; y += v.y; z += v.z; return *this; }
            self_type& operator -= (const self_type& v) { 
                x -= v.x; y -= v.y; z -= v.z; return *this; }
            self_type& operator *= (const self_type& v)	{ 
                x *= v.x; y *= v.y; z *= v.z; return *this; }
            self_type& operator /= (const self_type& v)	{ 
                x /= v.x; y /= v.y; z /= v.z; return *this; }

            self_type& operator /= (const value_type& f)	{ 
                x /= f; y /= f; z /= f; return *this; }
            self_type& operator *= (const value_type& f)	{ 
                x *= f; y *= f; z *= f; return *this; }
            
            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                char xs[10], ys[10], zs[10], buffer[32];
                dtostrf(x,4,2,xs); dtostrf(y,4,2,ys);
                int len = sprintf(buffer, "(%s %s %s)", xs, ys, zs);
                return std::basic_string<E, TAllocator, TStorage>(buffer, len);
	    }
            
	};
        template < typename T >
        inline vector3<T> operator + (const vector3<T>& a, const vector3<T>& b)					
            { return vector3<T> (a.x + b.x, a.y + b.y, a.z + b.z); }
	template < typename T >
        inline vector3<T> operator - (const vector3<T>& a, const vector3<T>& b)					
            { return vector3<T> (a.x - b.x, a.y - b.y, a.z - b.z); }
	template < typename T >
        inline vector3<T> operator - (const vector3<T>& a)										
            { return vector3<T> (-a.x, -a.y, -a.z); }
	template < typename T >
        inline vector3<T> operator * (const vector3<T>& a,const vector3<T>& b)						
            { return vector3<T> (a.x * b.x, a.y * b.y, a.z * b.z); }
	template < typename T >
        inline vector3<T> operator * (const vector3<T>& a, const T& b)						
            { return vector3<T> (a.x * b, a.y * b, a.z * b); }
	template < typename T >
        inline vector3<T> operator * (const T& a,const vector3<T>& b)						
            { return vector3<T> (a * b.x, a * b.y, a * b.z); }
        template < typename T >
        inline vector3<T> operator / (const vector3<T>& a,const vector3<T>& b)						
            { return vector3<T> (a.x / b.x, a.y / b.y, a.z / b.z); }
	template < typename T >
        inline vector3<T> operator / (const T& a,const vector3<T>& b)						
            { return vector3<T> (a / b.x, a / b.y, a / b.z); }
	template < typename T >
        inline vector3<T> operator / (const vector3<T>& a,const T& b)						
            { return vector3<T> (a.x / b, a.y / b, a.z / b); }

        template < typename T >
	inline bool operator == (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z)); }
	template < typename T >
        inline bool operator != (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z)); }
	template < typename T >
        inline bool operator <= (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z)); }
	template < typename T >
        inline bool operator >= (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z)); }
	template < typename T >
        inline bool operator < (const vector3<T>& a, const vector3<T>& b)							
            { return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z)); }
	template < typename T >
        inline bool operator > (const vector3<T>& a, const vector3<T>& b)							
            { return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z)); }
        template < typename T >
        inline T lenghtSq(const vector3<T>& v)									
            { return (v.x * v.x + v.y * v.y + v.z * v.z); }
        template < typename T >
	inline T lenght(const vector3<T>& v)									
            { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
        template < typename T >
	inline vector3<T> normalize(const vector3<T>& v)									
            { return v / (T)sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z)); }
        template < typename T >
	inline vector3<T> normalizex(const vector3<T>& v)								
            { return v / (T)(sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z)) + 0.0001); }
        template < typename T >
	inline vector3<T> cross(const vector3<T>& v1, vector3<T>& v2)						
            { return vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
	template < typename T >
        inline T dot(const vector3<T>& v1, const vector3<T>& v2)					
            { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
	template < typename T >
        inline T angle(const vector3<T>& v1, const vector3<T>& v2)				
            { return (T)(acos(double((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)) /
                        sqrt((double)((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)) * T((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z))))); }
	template < typename T >
        inline vector3<T> interpolate_coords(const vector3<T>& v1, const vector3<T>& v2, const float p)								
            { return v1 + p * (v2 - v1); }
	template < typename T >
        inline vector3<T> interpolate_normal(const vector3<T>& v1, const vector3<T>& v2, const float p)								
            { return normalize(v1 + p * (v2 - v1)); }
	template < typename T >
        inline bool nearequal(const vector3<T>& v1, vector3<T>& v2, const vector2<T>& epsilon)							
            { return ( abs(float(v1.x - v2.x )) <= epsilon && ( abs(float(v1.y - v2.y)) <= epsilon) && (abs(float(v1.z - v2.z)) <= epsilon)); }
   
        template <typename T>
        inline vector3<T> _min(const vector3<T>& c1, const vector3<T>& c2)
            {return vector3<T>(std::_min<T>(c1.x, c2.x), std::_min<T>(c1.y, c2.y), std::_min<T>(c1.z, c2.z));}
        template <typename T>
        inline vector3<T> _max(const vector3<T>& c1, const vector3<T>& c2)
            {return vector3<T>(std::_max<T>(c1.x, c2.x), std::_max<T>(c1.y, c2.y), std::_max<T>(c1.z, c2.z));}
	template <typename T>
        inline vector3<T> scale(const vector3<T>& v, const float s)
            {return vector3<T>(v.x * s, v.y*s, v.z*s);}
        
        
    }
    template<typename T, typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
    inline std::basic_string<E, TAllocator, TStorage> vec3_string(const std::math::vector3<T>& v, flags_t f = flags_t::dec  ) {   
            return v.to_string<E, TAllocator, TStorage>(); }


        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec3_string(const std::math::vec3f& v, flags_t f = flags_t::dec  ) {   
            return std::vec3_string<float, E, TAllocator, TStorage>(v); }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec3_string(const std::math::vec3d& v, flags_t f = flags_t::dec  ) {   
            return std::vec3_string<double, E, TAllocator, TStorage>(v); }
}

#endif /* VECTOR3_HPP */

