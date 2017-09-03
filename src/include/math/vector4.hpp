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
 * File:   vector4.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 02:17
 */

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "../unknown.hpp"
#include "vector3.hpp"

namespace std
{
    namespace math
    {
        template < typename T > class vector4;
        typedef vector4<float>  vec4f;
        typedef vector4<double> vec4d;
        
        
        template <typename T>
        class vector4 : public object
	{
	public:
            typedef T value_type;
            typedef vector4<T> self_type;
            typedef T* pointer;
            
            union
            {
                struct
                {
                    value_type x;
                    value_type y;
                    value_type z;
                    value_type w;
                };
                struct {
                    vector3<value_type> xyz;
                };
		float c[4];
            };
	    vector4(void)																		
                : x(0), y(0), z(0), w(0)							{}
	    vector4(const value_type _x, const value_type _y, const value_type _z, const value_type _w)	
                : x(_x), y(_y), z(_z), w(_w)					{}
            vector4(const value_type f)															
                : x(f), y(f), z(f), w(f)							{}
	    vector4(const self_type& vec)														
                : x(vec.x), y(vec.y), z(vec.z), w(vec.w)			{}
	    vector4(const vector3<T>& vec)														
                : x(vec.x), y(vec.y), z(vec.z), w(0)			{}
            vector4(const vector2<T>& vec)														
                : x(vec.x), y(vec.y), z(0), w(0)			{}
            vector4(const value_type *lpf)														
                : x(lpf[0]), y(lpf[1]), z(lpf[2]), w(lpf[3])		{}
		
	    operator value_type*	()														{ return (float*)(c); }
	    operator void*  ()														{ return (void*)(c); }
	
	    self_type& operator =  (const self_type& v)								{ x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
	    self_type& operator += (const self_type& v)								{ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	    self_type& operator -= (const self_type& v)								{ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	    self_type& operator *= (const self_type& v)								{ x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	    self_type& operator /= (const self_type& v)								{ x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

	    self_type& operator /= (const value_type& f)								{ x /= f; y /= f; z /= f; w /= f; return *this; }
	    self_type& operator *= (const value_type& f)								{ x *= f; y *= f; z *= f; w *= f; return *this; }
	
            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                char xs[8], ys[8], zs[8], ws[8], buffer[36];
                dtostrf(x,4,2,xs); dtostrf(y,4,2,ys); dtostrf(z,4,2,zs); dtostrf(w,4,2,ws);
                int len = sprintf(buffer, "(%s %s %s %s)", xs, ys, zs, ws);
                return std::basic_string<E, TAllocator, TStorage>(buffer, len);
	    }
        };
        template <typename T>
	inline vector4<T> operator + (const vector4<T>& a, const vector4<T>& b)					
            { return vector4<T> (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
        template <typename T>
	inline vector4<T> operator - (const vector4<T>& a, const vector4<T>& b)					
            { return vector4<T> (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
        template <typename T>
	inline vector4<T> operator - (const vector4<T>& v)										
            { return vector4<T> (-v.x, -v.y, -v.x, -v.w); }
        template <typename T>
	inline vector4<T> operator * (const vector4<T>& a,const vector4<T>& b)						
            { return vector4<T> (a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
        template <typename T>
	inline vector4<T> operator * (const vector4<T>& a, const T& b)						
            { return vector4<T> (a.x * b, a.y * b, a.z * b, a.w * b); }
        template <typename T>
	inline vector4<T> operator * (const T& a,const vector4<T>& b)						
            { return vector4<T> (a * b.x, a * b.y, a * b.z, a * b.w); }
        template <typename T>
	inline vector4<T> operator / (const vector4<T>& a,const vector4<T>& b)						
            { return vector4<T> (a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
        template <typename T>
	inline vector4<T> operator / (const T& a,const vector4<T>& b)						
            { return vector4<T> (a / b.x, a / b.y, a / b.z, a / b.w); }
        template <typename T>
	inline vector4<T> operator / (const vector4<T>& a,const T& b)						
            { return vector4<T> (a.x / b, a.y / b, a.z / b, a.w / b); }

        template <typename T>
	inline bool operator == (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w)); }
        template <typename T>
	inline bool operator != (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z) && (a.w != b.w)); }
        template <typename T>
	inline bool operator <= (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z) && (a.w <= b.w)); }
        template <typename T>
	inline bool operator >= (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z) && (a.w >= b.w)); }
        template <typename T>
	inline bool operator < (const vector4<T>& a, const vector4<T>& b)							
            { return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z) && (a.w < b.w)); }
        template <typename T>
	inline bool operator > (const vector4<T>& a, const vector4<T>& b)							
            { return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z) && (a.w > b.w)); }

        template <typename T>
	inline T	 lenghtSq(const vector4<T>& v)									
            { return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
        template <typename T>
	inline T	 lenght(const vector4<T>& v)									
            { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
        template <typename T>
	inline vector4<T> normalize(const vector4<T>& v)									
            { return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
        template <typename T>
	inline vector4<T> normalizex(const vector4<T>& v)								
            { return v / (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w) + 0.0001); }

        template <typename T>
	inline T	 dot(const vector4<T>& v1, const vector4<T>& v2)					
            { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;}
        template <typename T>
	inline T	 angle(const vector4<T>& v1, const vector4<T>& v2)				
            { return (T)acosf((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w) /
		     (T)sqrtf((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w) * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w))); }
	template <typename T>
        inline vector4<T> interpolate_coords(const vector4<T>& v1, const vector4<T>& v2, const T p)								
            { return v1 + p * (v2 - v1); }
        template <typename T>
	inline vector4<T> interpolate_normal(const vector4<T>& v1, const vector4<T>& v2, const T p)								
            { return normalize(v1 + p * (v2 - v1)); }
        template <typename T>
	inline bool		 near_equal(const vector4<T>& v1, vector4<T>& v2, const vector2<T>& epsilon)							
            { return ( abs((v1.x - v2.x) ) <= epsilon && ( abs(((v1.y - v2.y)) <= epsilon) )&& (abs((v1.z - v2.z)) <= epsilon) && (abs((v1.w - v2.w)) <= epsilon)); }
        template <typename T>
        inline vector4<T> scale(const vector4<T>& v, const float s)
            {return vector4<T>(v.x * s, v.y*s, v.z*s, v.w * s);}
        
    }
    template<typename T, typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
    inline std::basic_string<E, TAllocator, TStorage> vec4_string(const std::math::vector4<T>& v, flags_t f = flags_t::dec  ) {   
            return v.to_string<E, TAllocator, TStorage>(); }


        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec4_string(const std::math::vec4f& v, flags_t f = flags_t::dec  ) {   
            return std::vec4_string<float, E, TAllocator, TStorage>(v); }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> vec4_string(const std::math::vec4d& v, flags_t f = flags_t::dec  ) {   
            return std::vec4_string<double, E, TAllocator, TStorage>(v); }
}

#endif /* VECTOR4_HPP */

