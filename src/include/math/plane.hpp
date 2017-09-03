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
 * File:   plane.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 02:44
 */

#ifndef PLANE_HPP
#define PLANE_HPP

#include "vector4.hpp"

namespace std
{
    namespace math
    {
        template < typename T > class plane;
        typedef plane<float>  planef;
        typedef plane<double> planed;
        typedef plane<int>    planei;
        typedef plane<short>  planes;
        
        template <typename T>
        class plane : public vector4<T>
        {
        public:
            typedef T value_type;
            typedef plane<T> self_type;
            typedef T* pointer; 
            
            plane(void)																		
                : vector4<T>()							{}
	    plane(const value_type _x, const value_type _y, const value_type _z, const value_type _w)	
                : vector4<T>(_x, _y, _z, _w)					{}
            plane(const value_type f)															
                :  vector4<T>(f, f, f, f)								{}
	    plane(const self_type& vec)														
                : vector4<T>(vec.x, vec.y, vec.z, vec.w)			{}
	    plane(const vector3<T>& vec)														
                : vector4<T>(vec)			{}
            plane(const vector2<T>& vec)														
                : vector4<T>(vec)			{}
            plane(const value_type *lpf)														
                : vector4<T>(lpf)		{}
            
            virtual std::string to_string() {
                return vector4<T>::to_string();
            }
        };
        
        template <typename T>
        inline plane<T>	plane_frompointnormal(const vector3<T>& p, const vector3<T>& n)						
            {return plane<T>(n, -n.x * p.x - n.y * p.y - n.z * p.z);}
	template <typename T>
        inline plane<T>	plane_frompoints(const vector3<T>& v1, const vector3<T>& v2, const vector3<T>& v3)	
            {return plane_frompointnormal(v1, cross(v3 - v2, v1 - v2));}

    }
}

#endif /* PLANE_HPP */

