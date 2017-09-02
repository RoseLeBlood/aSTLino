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
 * File:   rectangle.hpp
 * Author: annas
 *
 * Created on 25. November 2016, 00:57
 */

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../algorithm.hpp"
#include "vector4.hpp"

namespace std 
{
    namespace math
    {
        template <typename T>
        class rectangle : public object
        {
        public:
            typedef typedef T value_type;
            typedef rectangle<T> self_type;
            typedef T* pointer;
            
            union
            {
                struct {
                    value_type x;
                    value_type y;
                    value_type width;
                    value_type height;
                };
                struct {
                    vector2<T> position;
                    vector2<T> size;
                };
                value_type c[4];
            };
            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                char xs[8], ys[8], zs[8], ws[8], buffer[36];
                dtostrf(x,4,2,xs); dtostrf(y,4,2,ys); dtostrf(width,4,2,zs); dtostrf(height,4,2,ws);
                int len = sprintf(buffer, "(%s %s %s %s)", xs, ys, zs, ws);
                return std::basic_string<E, TAllocator, TStorage>(buffer, len);
	    }
            rectangle() 
                : x(0), y(0), width(1), height(1) { }
            rectangle(value_type _x, value_type _y, value_type _w, value_type _h) 
                : x(_x), y(_y), width(_w), height(_h) { }
            rectangle(vector2<value_type> pos, vector2<value_type> size) 
                : x(pos.x), y(pos.y), width(size.x), height(size.y) { }
            
            const value_type& top() { return y; }
            void top(const value_type& t) { y = t; }
            
            const value_type& left() { return x; }
            void left(const value_type& t) { x = t; }
            
            const value_type& bottom() { return y + height; }
            const value_type& right() { return x + width; }
            
            vector2<value_type> center() { return vector2<T>(x + width / 2, y + height / 2); }
            vector2<value_type> size() { return vector2<value_type>(width, height); }
            
            rectangle<value_type> inflate (value_type leftRight, value_type topBottom)
	    {
	        x -= leftRight;
	        width += leftRight * 2;
	        y -= topBottom;
		height += topBottom * 2;

		return this;
            }
            bool contains(rectangle<T> r)
            {
               return r.left() >= left() && r.right() <= right() &&
                       r.top() >= top() && r.bottom() <= bottom();
            }
            rectangle<value_type>& intersect(const rectangle<value_type>& r1, const rectangle<value_type>& r2)
            {
                int x = std::_max<value_type> (r1.x, r2.x);
		int y = std::_max<value_type> (r1.y, r2.y);
		int w = std::_min<value_type> (r1.right(), r2.right()) - x;
		int h = std::_min<value_type> (r1.bottom(), r2.bottom()) - y;
		return rectangle<value_type>(x,y,w,h);
            }
            bool intersects(const rectangle<value_type>& r)
            {
                int w = std::_min<value_type> (r.right(), right()) - std::_max<value_type> (r.x, x);
		int h = std::_min<value_type> (r.bottom(), bottom()) - std::_max<value_type> (r.y, y);
		return w > 0 && h > 0;
            }
            void offset(float offx, float offy)
            {
                x += offx;
                y += offy;
            }
        };
        template <typename T>
        inline bool operator == (rectangle<T> a, rectangle<T> b)
        {
            return a.x == b.x && a.y == b.y && a.width == b.width && a.height && b.height;
        }
        template <typename T>
        inline bool operator != (rectangle<T> a, rectangle<T> b)
        {
            return a.x != b.x && a.y != b.y && a.width != b.width && a.height != b.height;
        }
    }
}

#endif /* RECTANGLE_HPP */

