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
 * File:   ext.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 22:24
 */

#ifndef EXT_HPP
#define EXT_HPP

#include "matrix4x4.hpp"
#include "quaternion.hpp"

namespace std
{
    namespace math
    {
        template <typename T>
        inline matrix4x4<T> tomatrix(const quaternion<T>& v)
        {
            return matrix4x4<T>(v.s, -v.v.x, -v.v.y, -v.v.z,
			    v.v.x, v.s,	 -v.v.z, v.v.y,
			    v.v.y, v.v.z, v.s, -v.v.x,
			    v.v.z, -v.v.y, v.v.x, v.s);
        }
        template <typename T> 
        inline quaternion<T> toquaternion(const matrix4x4<T>& mat)
        { 
            quaternion<T> v;
            T tmp = fabs(mat(1,1) + mat(2,2) + mat(3,3) + 1);
            v.s = 0.5f*sqrt(tmp);

            if(v.s > 0.0000001f)
            {
                v.v.x = (mat.n[9]-mat.n[6])/(4*v.s);
                v.v.y = (mat.n[2]-mat.n[8])/(4*v.s);
                v.v.z = (mat.n[4]-mat.n[1])/(4*v.s);
            }
            else
            {
               static int s_iNext[3] = { 2, 3, 1 };
               int i = 1;
               if ( mat(2,2) > mat(1,1) )
                  i = 2;
               if ( mat(3,3) > mat(2,2) )
                  i = 3;
               int j = s_iNext[i-1];
               int k = s_iNext[j-1];

               T fRoot = sqrt(mat(i,i)-mat(j,j)-mat(k,k) + 1.0);

               T *tmp[3] = { (T*)&v.v.x, (T*)&v.v.y, (T*)&v.v.z };
               *tmp[i-1] = 0.5*fRoot;
               fRoot = 0.5/fRoot;
               v.s = (mat(k,j)-mat(j,k))*fRoot;
               *tmp[j-1] = (mat(j,i)+mat(i,j))*fRoot;
               *tmp[k-1] = (mat(k,i)+mat(i,k))*fRoot;
            }
        }
        template <typename T>
        vector3<T> transformcoord(const vector3<T>& v, const matrix4x4<T>& m)
        {
            T norm = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3];

            if ( norm == 1 )
                return vector3<T>(
                    (m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0]) / norm, 
                    (m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1]) / norm, 
                    (m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2]) / norm);
            else
                return vector3<T>(0);
        }
        template <typename T>
        vector3<T> transformnormal(const vector3<T>& v, const matrix4x4<T>& m)
        {
            return vector3<T>(
                m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z,
                m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z,
                m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z);
        }


    }
}

#endif /* EXT_HPP */

