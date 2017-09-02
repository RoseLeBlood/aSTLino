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
 * File:   color.hpp
 * Author: annas
 *
 * Created on 12. November 2016, 22:36
 */

#ifndef COLOR_HPP
#define COLOR_HPP

//#include <math>
#include "../unknown.hpp"
#include "../algorithm.hpp"

namespace std
{
    namespace math
    {
        template < typename T > class color;
        typedef color<float>  colf;
        typedef color<double> cold;
        
        template < typename T >
        class color : public std::object
        {
            const T colorcon = 0.003921568627450980392156862745098;
        public:   
            typedef T value_type;
            typedef T* pointer;
            typedef color<T> self_type;
            union
	    {
                struct {
                    value_type r;
                    value_type g;
                    value_type b;
                    value_type a;
                };
                struct {
                    value_type red;
                    value_type green;
                    value_type blue;
                    value_type alpha;
                };
                value_type c[4];
            };
	    color(void) 																																															{}
	    color(value_type _r, value_type _g, value_type _b, value_type _a)	: r(_r), g(_g), b(_b), a(_a)																															{}
	    color(value_type _r, value_type _g, value_type _b) : r(_r), g(_g), b(_b), a(1.0)																																	{}
	    color(value_type f) : r(f), g(f), b(f), a(f)																																								{}
	    color(value_type *com) : r(com[0]), g(com[1]), b(com[2]), a(com[3])																																	{}
	    color(const int _r, const int _g, const int _b) : r((T)(_r) * colorcon), g((T)(_g) * colorcon), b((T)(_b) * colorcon), a(1.0f)														{}
	    color(const int _r, const int _g, const int _b, const int _a) : r((T)(_r) * colorcon), g((T)(_g) * colorcon), b((T)(_b) * colorcon), a((T)(_a) * colorcon)					{}
	    color(const int* pComponent) : r((T)(pComponent[0]) * colorcon), g((T)(pComponent[1]) * colorcon), b((T)(pComponent[2]) * colorcon), a((T)(pComponent[3]) * colorcon)		{}
	    color(const int c) : r(colorcon * (T)(c >> 16)), g(colorcon * (T)(c >> 8)), b(colorcon * (T)(c)), a(colorcon * (T)(c >> 24))							{}

	    operator unsigned long () const
	    {
		return ((a >= 1.0f ? 255 : a <= 0.0f ? 0 : (unsigned long)(a * 255.0f)) << 24) |
                    ((r >= 1.0f ? 255 : r <= 0.0f ? 0 : (unsigned long)(r * 255.0f)) << 16) |
                    ((g >= 1.0f ? 255 : g <= 0.0f ? 0 : (unsigned long)(g * 255.0f)) << 8)  |
                    (b >= 1.0f ? 255 : b <= 0.0f ? 0 : (unsigned long)(b * 255.0f));
            }
            operator T* ()			{return (T*)(c);}
		
            self_type& operator = (const self_type& c)	{a = c.a; b = c.b; g = c.g; r = c.r; return *this;}
	    self_type& operator += (const self_type& c)	{r += c.r; g += c.g; b += c.b; a += c.a; return *this;}
	    self_type& operator -= (const self_type& c)	{r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this;}
	    self_type& operator *= (const self_type& c)	{r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this;}
	    self_type& operator *= (const value_type f)	{r *= f; g *= f; b *= f; a *= f; return *this;}
	    self_type& operator /= (const self_type& c)	{r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this;}
	    self_type& operator /= (const value_type f)	{r /= f; g /= f; b /= f; a /= f; return *this;}
       
            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                char xs[8], ys[8], zs[8], ws[8], buffer[36];
                dtostrf(r,4,2,xs); dtostrf(g,4,2,ys); dtostrf(b,4,2,zs); dtostrf(a,4,2,ws);
                int len = sprintf(buffer, "(%s %s %s %s)", xs, ys, zs, ws);
                return std::basic_string<E, TAllocator, TStorage>(buffer, len);
	    }
        };
        template <typename T>
        inline color<T> operator + (const color<T>& a, const color<T>& b)	
            {return color<T>(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);}
	template <typename T>
        inline color<T> operator - (const color<T>& a, const color<T>& b)	
            {return color<T>(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);}
	template <typename T>
        inline color<T> operator - (const color<T>& c)					
            {return color<T>(-c.r, -c.g, -c.b, c.a);}
	template <typename T>
        inline color<T> operator * (const color<T>& a, const color<T>& b)	
            {return color<T>(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);}
	template <typename T>
        inline color<T> operator * (const color<T>& c, const T f)		
            {return color<T>(c.r * f, c.g * f, c.b * f, c.a * f);}
	template <typename T>
        inline color<T> operator * (const T f, const color<T>& c)		
            {return color<T>(c.r * f, c.g * f, c.b * f, c.a * f);}
	template <typename T>
        inline color<T> operator / (const color<T>& a, const color<T>& b)	
            {return color<T>(a.r / b.r, a.g / b.g, a.b / b.b, a.a / b.a);}
	template <typename T>
        inline color<T> operator / (const color<T>& c, const T f)		
            {return color<T>(c.r / f, c.g / f, c.b / f, c.a / f);}

	// Vergleichsoperatoren
        template <typename T>
	inline bool operator == (const color<T>& a, const color<T>& b)
            {if(a.r != b.r) return false; if(a.g != b.g) return false; if(a.b != b.b) return false; return a.a == b.a;}
	template <typename T>
        inline bool operator != (const color<T>& a, const color<T>& b) 
            {if(a.r != b.r) return true; if(a.g != b.g) return true; if(a.b != b.b) return true; return a.a != b.a;}

	// ******************************************************************
	// Funktionen deklarieren
        template <typename T>
	inline color<T>	negate(const color<T>& c)
            {return color<T>(1.0f - c.r, 1.0f - c.g, 1.0f - c.b, 1.0f - c.a);}
	template <typename T>
        inline T	brightness(const color<T>& c)	
            {return c.r * 0.299f + c.g * 0.587f + c.b * 0.114f;}
	template <typename T>
        inline color<T>	interpolate(const color<T>& c1, const color<T>& c2, const T p)
        	{return c1 + p * (c2 - c1);}
	template <typename T>
        inline color<T>	_min(const color<T>& c1, const color<T>& c2)
            {return color<T>(std::_min<T>(c1.r, c2.r), std::_min<T>(c1.g, c2.g), std::_min<T>(c1.b, c2.b), std::_min<T>(c1.a, c2.a));}
	template <typename T>
        inline color<T>	_max(const color<T>& c1, const color<T>& c2)
            {return color<T>(std::_max<T>(c1.r, c2.r), std::_max<T>(c1.g, c2.g), std::_max<T>(c1.b, c2.b), std::_max<T>(c1.a, c2.a));}
	
        template <typename T>
        color<T> from_yuv(const T y, const T u, const T v) {
            return color<T>(T(1.164 * (y - 16) + 1.596*(v - 128)), 
                            T(1.164 * (y - 16) - 0.813*(v - 128) - 0.391*(u - 128)), 
                            T(1.164 * (y - 16) + 2.018*(u - 128)));
        }
        template <typename T>
	color<T> from_cmy(const T c, const T m, const T y) {
            return color<T>( T(1.0 - c), T(1.0 - m), T(1.0 - y));
        }
        template <typename T>
	color<T> from_hsv(const T h, const T s, const T v) {
            if( s == 0 ) return color<T>(v,v,v);
            
            T i, f, p, q, t;
            
            h /= 60;			// sector 0 to 5
            i = floor( h );
            f = h - i;			// factorial part of h
            p = v * ( 1 - s );
            q = v * ( 1 - s * f );
            t = v * ( 1 - s * ( 1 - f ) );

            if(i == 0) return color<T>(v, t, p);
            if(i == 1) return color<T>(q, v, p);
            if(i == 2) return color<T>(p, v, t);
            if(i == 3) return color<T>(p, q, v);
            if(i == 4) return color<T>(t, p, v);

            return raColor(v, p, q);
        }
    }
}

#endif /* COLOR_HPP */

