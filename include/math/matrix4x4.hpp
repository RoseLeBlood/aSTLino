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
 * File:   matrix4x4.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 18:46
 */

#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include "vector4.hpp"
#include "utils.hpp"

namespace std
{
    namespace math
    {
        template < typename T> 
        class matrix4x4;
    
        template < typename T> 
        matrix4x4<T> invert(const matrix4x4<T>& mat);
        
        typedef matrix4x4<float> mat4f;
        typedef matrix4x4<double> mat4d;
        
        
        template < typename T> 
        class matrix4x4
        {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef matrix4x4<T> self_type;
            
            union
            {
		struct
		{
                    T m11, m12, m13, m14,
		      m21, m22, m23, m24,
		      m31, m32, m33, m34,
		      m41, m42, m43, m44;
		};
                struct 
                {
                    vector4<value_type> row0;
                    vector4<value_type> row1;
                    vector4<value_type> row2;
                    vector4<value_type> row3; 
                };
		float		m[4][4];
		float		n[16];
            };
            matrix4x4(const self_type& m) : m11(m.m11), m12(m.m12), m13(m.m13), m14(m.m14),
									  m21(m.m21), m22(m.m22), m23(m.m23), m24(m.m24),
									  m31(m.m31), m32(m.m32), m33(m.m33), m34(m.m34),
									  m41(m.m41), m42(m.m42), m43(m.m43), m44(m.m44)					{}

	    matrix4x4(value_type _m11, value_type _m12, value_type _m13, value_type _m14,
                      value_type _m21, value_type _m22, value_type _m23, value_type _m24,
		      value_type _m31, value_type _m32, value_type _m33, value_type _m34,
                      value_type _m41, value_type _m42, value_type _m43, value_type _m44) : m11(_m11), m12(_m12), m13(_m13), m14(_m14),
																   m21(_m21), m22(_m22), m23(_m23), m24(_m24),
																   m31(_m31), m32(_m32), m33(_m33), m34(_m34),
																   m41(_m41), m42(_m42), m43(_m43), m44(_m44)	{}

	    operator pointer ()					{return (pointer)(n);}
            value_type& operator () (int iRow, int iColumn) {return m[iRow - 1][iColumn - 1];}
	    value_type operator () (int iRow, int iColumn) const {return m[iRow - 1][iColumn - 1];}

            self_type& operator += (const self_type& m)
            {
		m11 += m.m11; m12 += m.m12; m13 += m.m13; m14 += m.m14;
		m21 += m.m21; m22 += m.m22; m23 += m.m23; m24 += m.m24;
		m31 += m.m31; m32 += m.m32; m33 += m.m33; m34 += m.m34;
		m41 += m.m41; m42 += m.m42; m43 += m.m43; m44 += m.m44;
		return *this;
            }

            self_type& operator -= (const self_type& m)
            {
		m11 -= m.m11; m12 -= m.m12; m13 -= m.m13; m14 -= m.m14;
		m21 -= m.m21; m22 -= m.m22; m23 -= m.m23; m24 -= m.m24;
		m31 -= m.m31; m32 -= m.m32; m33 -= m.m33; m34 -= m.m34;
		m41 -= m.m41; m42 -= m.m42; m43 -= m.m43; m44 -= m.m44;
		return *this;
            }
            self_type& operator *= (const self_type& m)
	    {
		 return *this = self_type(m.m11 * m11 + m.m21 * m12 + m.m31 * m13 + m.m41 * m14,
					  m.m12 * m11 + m.m22 * m12 + m.m32 * m13 + m.m42 * m14,
					  m.m13 * m11 + m.m23 * m12 + m.m33 * m13 + m.m43 * m14,
					  m.m14 * m11 + m.m24 * m12 + m.m34 * m13 + m.m44 * m14,
					  m.m11 * m21 + m.m21 * m22 + m.m31 * m23 + m.m41 * m24,
					  m.m12 * m21 + m.m22 * m22 + m.m32 * m23 + m.m42 * m24,
					  m.m13 * m21 + m.m23 * m22 + m.m33 * m23 + m.m43 * m24,
					  m.m14 * m21 + m.m24 * m22 + m.m34 * m23 + m.m44 * m24,
					  m.m11 * m31 + m.m21 * m32 + m.m31 * m33 + m.m41 * m34,
					  m.m12 * m31 + m.m22 * m32 + m.m32 * m33 + m.m42 * m34,
					  m.m13 * m31 + m.m23 * m32 + m.m33 * m33 + m.m43 * m34,
					  m.m14 * m31 + m.m24 * m32 + m.m34 * m33 + m.m44 * m34,
					  m.m11 * m41 + m.m21 * m42 + m.m31 * m43 + m.m41 * m44,
					  m.m12 * m41 + m.m22 * m42 + m.m32 * m43 + m.m42 * m44,
					  m.m13 * m41 + m.m23 * m42 + m.m33 * m43 + m.m43 * m44,
					  m.m14 * m41 + m.m24 * m42 + m.m34 * m43 + m.m44 * m44);
            }

            self_type& operator *= (const value_type f)
            {
			m11 *= f; m12 *= f; m13 *= f; m14 *= f;
			m21 *= f; m22 *= f; m23 *= f; m24 *= f;
			m31 *= f; m32 *= f; m33 *= f; m34 *= f;
			m41 *= f; m42 *= f; m43 *= f; m44 *= f;
			return *this;
            }
            self_type& operator /= (const self_type& m)
	    {
		return *this *= invert(m);
	    }

	    self_type& operator /= (const value_type f)
	    {
		m11 /= f; m12 /= f; m13 /= f; m14 /= f;
		m21 /= f; m22 /= f; m23 /= f; m24 /= f;
		m31 /= f; m32 /= f; m33 /= f; m34 /= f;
		m41 /= f; m42 /= f; m43 /= f; m44 /= f;
		return *this;
	    }
            
            

            template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            std::basic_string<E, TAllocator, TStorage> to_string() {   
                 char buffer[256];
                 int len = sprintf(buffer, "%s\n%s\n%s\n%s", 
			row0.to_string().c_str(), row1.to_string().c_str(), row2.to_string().c_str(), row3.to_string().c_str());
                 return std::string(buffer, len);
            }
        };
        template <typename T>
        inline matrix4x4<T> operator + (const matrix4x4<T>& a, const matrix4x4<T>& b)	
            {return matrix4x4<T>(a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13, a.m14 + b.m14, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23, a.m24 + b.m24, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33, a.m34 + b.m34, a.m41 + b.m41, a.m42 + b.m42, a.m43 + b.m43, a.m44 + b.m44);}
	template <typename T>
        inline matrix4x4<T> operator - (const matrix4x4<T>& a, const matrix4x4<T>& b)	
            {return matrix4x4<T>(a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13, a.m14 - b.m14, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23, a.m24 - b.m24, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33, a.m34 - b.m34, a.m41 - b.m41, a.m42 - b.m42, a.m43 - b.m43, a.m44 - b.m44);}
	template <typename T>
        inline matrix4x4<T> operator - (const matrix4x4<T>& m)						
            {return matrix4x4<T>(-m.m11, -m.m12, -m.m13, -m.m14, -m.m21, -m.m22, -m.m23, -m.m24, -m.m31, -m.m32, -m.m33, -m.m34, -m.m41, -m.m42, -m.m43, -m.m44);}
        template <typename T>
        inline matrix4x4<T> operator * (const matrix4x4<T>& a, const matrix4x4<T>& b)
	{
		return matrix4x4<T>(b.m11 * a.m11 + b.m21 * a.m12 + b.m31 * a.m13 + b.m41 * a.m14,
						b.m12 * a.m11 + b.m22 * a.m12 + b.m32 * a.m13 + b.m42 * a.m14,
						b.m13 * a.m11 + b.m23 * a.m12 + b.m33 * a.m13 + b.m43 * a.m14,
						b.m14 * a.m11 + b.m24 * a.m12 + b.m34 * a.m13 + b.m44 * a.m14,
						b.m11 * a.m21 + b.m21 * a.m22 + b.m31 * a.m23 + b.m41 * a.m24,
						b.m12 * a.m21 + b.m22 * a.m22 + b.m32 * a.m23 + b.m42 * a.m24,
						b.m13 * a.m21 + b.m23 * a.m22 + b.m33 * a.m23 + b.m43 * a.m24,
						b.m14 * a.m21 + b.m24 * a.m22 + b.m34 * a.m23 + b.m44 * a.m24,
						b.m11 * a.m31 + b.m21 * a.m32 + b.m31 * a.m33 + b.m41 * a.m34,
						b.m12 * a.m31 + b.m22 * a.m32 + b.m32 * a.m33 + b.m42 * a.m34,
						b.m13 * a.m31 + b.m23 * a.m32 + b.m33 * a.m33 + b.m43 * a.m34,
						b.m14 * a.m31 + b.m24 * a.m32 + b.m34 * a.m33 + b.m44 * a.m34,
						b.m11 * a.m41 + b.m21 * a.m42 + b.m31 * a.m43 + b.m41 * a.m44,
						b.m12 * a.m41 + b.m22 * a.m42 + b.m32 * a.m43 + b.m42 * a.m44,
						b.m13 * a.m41 + b.m23 * a.m42 + b.m33 * a.m43 + b.m43 * a.m44,
						b.m14 * a.m41 + b.m24 * a.m42 + b.m34 * a.m43 + b.m44 * a.m44);
	}
        template <typename T>
	inline matrix4x4<T> operator * (const matrix4x4<T>& m, const T f)
	{
		return matrix4x4<T>(m.m11 * f, m.m12 * f, m.m13 * f, m.m14 * f,
						m.m21 * f, m.m22 * f, m.m23 * f, m.m24 * f,
						m.m31 * f, m.m32 * f, m.m33 * f, m.m34 * f,
						m.m41 * f, m.m42 * f, m.m43 * f, m.m44 * f);
	}
        template <typename T>
	inline matrix4x4<T> operator * (const T f, const matrix4x4<T>& m)
	{
		return matrix4x4<T>(m.m11 * f, m.m12 * f, m.m13 * f, m.m14 * f,
						m.m21 * f, m.m22 * f, m.m23 * f, m.m24 * f,
						m.m31 * f, m.m32 * f, m.m33 * f, m.m34 * f,
						m.m41 * f, m.m42 * f, m.m43 * f, m.m44 * f);
	}
        template <typename T>
	inline matrix4x4<T> operator / (const matrix4x4<T>& a, const matrix4x4<T>& b) 
            {return a * invert(b);}
        template <typename T>
	inline matrix4x4<T> operator / (const matrix4x4<T>& m, const T f)
	{
		return matrix4x4<T>(m.m11 / f, m.m12 / f, m.m13 / f, m.m14 / f,
						m.m21 / f, m.m22 / f, m.m23 / f, m.m24 / f,
						m.m31 / f, m.m32 / f, m.m33 / f, m.m34 / f,
						m.m41 / f, m.m42 / f, m.m43 / f, m.m44 / f);
	}
        template <typename T>
	inline bool operator == (const matrix4x4<T>& a, const matrix4x4<T>& b)
	{
		if(a.m11 != b.m11) return false;
		if(a.m12 != b.m12) return false;
		if(a.m13 != b.m13) return false;
		if(a.m14 != b.m14) return false;
		if(a.m21 != b.m21) return false;
		if(a.m22 != b.m22) return false;
		if(a.m23 != b.m23) return false;
		if(a.m24 != b.m24) return false;
		if(a.m31 != b.m31) return false;
		if(a.m32 != b.m32) return false;
		if(a.m33 != b.m33) return false;
		if(a.m34 != b.m34) return false;
		if(a.m41 != b.m41) return false;
		if(a.m42 != b.m42) return false;
		if(a.m43 != b.m43) return false;
		return a.m44 == b.m44;
	}

	template <typename T>
	inline bool operator != (const matrix4x4<T>& a,  const matrix4x4<T>& b)
	{
		if(a.m11 != b.m11) return true;
		if(a.m12 != b.m12) return true;
		if(a.m13 != b.m13) return true;
		if(a.m14 != b.m14) return true;
		if(a.m21 != b.m21) return true;
		if(a.m22 != b.m22) return true;
		if(a.m23 != b.m23) return true;
		if(a.m24 != b.m24) return true;
		if(a.m31 != b.m31) return true;
		if(a.m32 != b.m32) return true;
		if(a.m33 != b.m33) return true;
		if(a.m34 != b.m34) return true;
		if(a.m41 != b.m41) return true;
		if(a.m42 != b.m42) return true;
		if(a.m43 != b.m43) return true;
		return a.m44 != b.m44;
	}
        template <typename T>
        inline	matrix4x4<T>	matrix4x4_identity() {return matrix4x4<T>(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);}
        template <typename T>
        inline matrix4x4<T> translate(const matrix4x4<T>& mat, const vector3<T>& v)
        {
            matrix4x4<T> m = mat;
            m.n[0] += m.n[3] * v.x;   m.n[4] += m.n[7] * v.x;   m.n[8] += m.n[11]* v.x;   m.n[12]+= m.n[15]* v.x;
            m.n[1] += m.n[3] * v.y;   m.n[5] += m.n[7] * v.y;   m.n[9] += m.n[11]* v.y;   m.n[13]+= m.n[15]* v.y;
            m.n[2] += m.n[3] * v.z;   m.n[6] += m.n[7] * v.z;   m.n[10]+= m.n[11]* v.z;   m.n[14]+= m.n[15]* v.z;

            return m;
        }
        template <typename T>
        inline matrix4x4<T> rotate(const matrix4x4<T>& mat, const vector3<T>& v, const T angle)
        {
             matrix4x4<T> m = mat;
             T c = (T)cos(angle * DEG2RAD);    // cosine
             T s = sin(angle * DEG2RAD);    // sine
             T c1 = (T)(1.0) - c;                // 1 - c
             T x = v.x, y = v.y, z = v.z;
             T m0 = m.n[0],  m4 = m.n[4],  m8 = m.n[8],  m12= m.n[12],
               m1 = m.n[1],  m5 = m.n[5],  m9 = m.n[9],  m13= m.n[13],
               m2 = m.n[2],  m6 = m.n[6],  m10= m.n[10], m14= m.n[14];

            // build rotation matrix
           T r0 = x * x * c1 + c;
           T r1 = x * y * c1 + z * s;
           T r2 = x * z * c1 - y * s;
           T r4 = x * y * c1 - z * s;
           T r5 = y * y * c1 + c;
           T r6 = y * z * c1 + x * s;
           T r8 = x * z * c1 + y * s;
           T r9 = y * z * c1 - x * s;
           T r10= z * z * c1 + c;

            m.n[0] = r0 * m0 + r4 * m1 + r8 * m2;
            m.n[1] = r1 * m0 + r5 * m1 + r9 * m2;
            m.n[2] = r2 * m0 + r6 * m1 + r10* m2;
            m.n[4] = r0 * m4 + r4 * m5 + r8 * m6;
            m.n[5] = r1 * m4 + r5 * m5 + r9 * m6;
            m.n[6] = r2 * m4 + r6 * m5 + r10* m6;
            m.n[8] = r0 * m8 + r4 * m9 + r8 * m10;
            m.n[9] = r1 * m8 + r5 * m9 + r9 * m10;
            m.n[10]= r2 * m8 + r6 * m9 + r10* m10;
            m.n[12]= r0 * m12+ r4 * m13+ r8 * m14;
            m.n[13]= r1 * m12+ r5 * m13+ r9 * m14;
            m.n[14]= r2 * m12+ r6 * m13+ r10* m14;
            return m;
        }
        template <typename T>
	inline matrix4x4<T>& rotateX(const matrix4x4<T> mat, const T angle)
        {
            matrix4x4<T> m = mat;
            T c = (T)cos(angle * DEG2RAD);
            T s = (T)sin(angle * DEG2RAD);
            T m1 = m.n[1],  m2 = m.n[2],
                  m5 = m.n[5],  m6 = m.n[6],
                  m9 = m.n[9],  m10= m.n[10],
                  m13= m.n[13], m14= m.n[14];

            m.n[1] = m1 * c + m2 *-s;
            m.n[2] = m1 * s + m2 * c;
            m.n[5] = m5 * c + m6 *-s;
            m.n[6] = m5 * s + m6 * c;
            m.n[9] = m9 * c + m10*-s;
            m.n[10]= m9 * s + m10* c;
            m.n[13]= m13* c + m14*-s;
            m.n[14]= m13* s + m14* c;

            return m;
        }
        template <typename T>
	inline matrix4x4<T>& rotateY(const matrix4x4<T> mat, const T angle)
        {
            matrix4x4<T> m = mat;
            T c = (T)cos(angle * DEG2RAD);
            T s = (T)sin(angle * DEG2RAD);
            T m0 = m.n[0],  m2 = m.n[2],
                  m4 = m.n[4],  m6 = m.n[6],
                  m8 = m.n[8],  m10= m.n[10],
                  m12= m.n[12], m14= m.n[14];

            m.n[0] = m0 * c + m2 * s;
            m.n[2] = m0 *-s + m2 * c;
            m.n[4] = m4 * c + m6 * s;
            m.n[6] = m4 *-s + m6 * c;
            m.n[8] = m8 * c + m10* s;
            m.n[10]= m8 *-s + m10* c;
            m.n[12]= m12* c + m14* s;
            m.n[14]= m12*-s + m14* c;

            return m;
        }
        template <typename T>
        inline matrix4x4<T>& rotateZ(const matrix4x4<T> mat, const T angle)
        {
            matrix4x4<T> m = mat;
            T c = (T)cos(angle * DEG2RAD);
            T s = (T)sin(angle * DEG2RAD);
            T m0 = m.n[0],  m1 = m.n[1],
                  m4 = m.n[4],  m5 = m.n[5],
                  m8 = m.n[8],  m9 = m.n[9],
                  m12= m.n[12], m13= m.n[13];

            m.n[0] = m0 * c + m1 *-s;
            m.n[1] = m0 * s + m1 * c;
            m.n[4] = m4 * c + m5 *-s;
            m.n[5] = m4 * s + m5 * c;
            m.n[8] = m8 * c + m9 *-s;
            m.n[9] = m8 * s + m9 * c;
            m.n[12]= m12* c + m13*-s;
            m.n[13]= m12* s + m13* c;

            return m;
        }
        template <typename T>
        inline matrix4x4<T> transpose(const matrix4x4<T>& mat)
        {
            matrix4x4<T> m = mat;
            std::swap<T>(m.n[1],  m.n[4]);
            std::swap<T>(m.n[2],  m.n[8]);
            std::swap<T>(m.n[3],  m.n[12]);
            std::swap<T>(m.n[6],  m.n[9]);
            std::swap<T>(m.n[7],  m.n[13]);
            std::swap<T>(m.n[11], m.n[14]);

            return m;
        }
        template <typename T>
        inline T cofactor(T m0, T m1, T m2,
                          T m3, T m4, T m5,
                          T m6, T m7, T m8) 
        {
            return  m0 * (m4 * m8 - m5 * m7) -
                    m1 * (m3 * m8 - m5 * m6) +
                    m2 * (m3 * m7 - m4 * m6);
        }
        template <typename T>
        inline T det(const matrix4x4<T>& m)
        {
            
            return  m.n[0] * cofactor<T>(m.n[5],m.n[6],m.n[7], m.n[9],m.n[10],m.n[11], m.n[13],m.n[14],m.n[15]) -
                    m.n[1] * cofactor<T>(m.n[4],m.n[6],m.n[7], m.n[8],m.n[10],m.n[11], m.n[12],m.n[14],m.n[15]) +
                    m.n[2] * cofactor<T>(m.n[4],m.n[5],m.n[7], m.n[8],m.n[9], m.n[11], m.n[12],m.n[13],m.n[15]) -
                    m.n[3] * cofactor<T>(m.n[4],m.n[5],m.n[6], m.n[8],m.n[9], m.n[10], m.n[12],m.n[13],m.n[14]);
        }
        template <typename T>
        inline vector3<T> angle(const matrix4x4<T>& m) 
        {
            T pitch, yaw, roll;         // 3 angles

            yaw = (RAD2DEG * (T)asin(m.n[8]));
            if(m.n[10] < 0)
            {
                if(yaw >= 0) yaw = 180.0f - yaw;
                else         yaw =-180.0f - yaw;
            }

            if(m.n[0] > -EPSILON && m.n[0] < EPSILON)
            {
                roll  = 0;  
                pitch = (RAD2DEG * atan2(m.n[1], m.n[5]));
            }
            else
            {
                roll = (RAD2DEG * atan2(-m.n[4], m.n[0]));
                pitch = (RAD2DEG * atan2(-m.n[9], m.n[10]));
            }

            return vector3<T>(pitch, yaw, roll);
        }
        template <typename T>
        inline matrix4x4<T> column(const matrix4x4<T> mat, int index, vector3<T> v)
        {
            matrix4x4<T> m = mat;
            m.n[index*4] = v.x;  m.n[index*4 + 1] = v.y;  m.n[index*4 + 2] = v.z;
            return m;
        } 
        template <typename T>
        inline matrix4x4<T> row(const matrix4x4<T> mat, int index, vector3<T> v)
        {
            matrix4x4<T> m = mat;
            m.n[index] = v.x;  m.n[index + 4] = v.y;  m.n[index + 8] = v.z;
            return m;
        } 
        template <typename T>
        inline matrix4x4<T> column(const matrix4x4<T> mat, int index, vector4<T> v)
        {
            matrix4x4<T> m = mat;
            m.n[index*4] = v.x;  m.n[index*4 + 1] = v.y;  m.n[index*4 + 2] = v.z;
            m.n[index*4 + 3] = v.w;
            return m;
        } 
        template <typename T>
        inline matrix4x4<T> row(const matrix4x4<T> mat, int index, vector4<T> v)
        {
            matrix4x4<T> m = mat;
            m.n[index] = v.x;  m.n[index + 4] = v.y;  m.n[index + 8] = v.z;
            m.n[index + 12] = v.w;
            return m;
        } 
       
        template <typename T>
        inline matrix4x4<T> lockat(const vector3<T> position, const vector3<T>& target, 
                const vector3<T>& vUp = vector3<T>(0,1,0))
        {
            vector3<T> forward = target - position;
            forward = normalize(forward);
            
            vector3<T> left = cross(vUp, forward);
            left = normalize(left);
    
            vector3<T> up = cross(forward, left);
            up = normalize(up);
            
            matrix4x4<T> m = matrix4x4_identity<T>();
            m.m11 = left.x;  m.m12 = left.y;  m.m13 = left.z;
            m.m21 = up.x;  m.m22 = up.y;  m.m23 = up.z;
            m.m31 = forward.x;  m.m32 = forward.y;  m.m33 = forward.z;

            return m;
        }
        template <typename T>
        inline matrix4x4<T> lockat(const matrix4x4<T> m, const vector3<T>& target, 
                const vector3<T>& vUp = vector3<T>(0,1,0))
        {
            return lockat<T>(vector3<T>(m.n[12], m.n[13], m.n[14]), target, vUp);
        }
        template < typename T> 
        inline matrix4x4<T> invert(const matrix4x4<T>& m)
        {
            T fInvDet = det<T>(m);
            if(fInvDet == 0) return matrix4x4_identity<T>();
            fInvDet = 1 / fInvDet;

            matrix4x4<T> mResult;
            mResult.m11 =  fInvDet * (m.m22 * m.m33 - m.m23 * m.m32);
            mResult.m12 = -fInvDet * (m.m12 * m.m33 - m.m13 * m.m32);
            mResult.m13 =  fInvDet * (m.m12 * m.m23 - m.m13 * m.m22);
            mResult.m14 =  0;
            mResult.m21 = -fInvDet * (m.m21 * m.m33 - m.m23 * m.m31);
            mResult.m22 =  fInvDet * (m.m11 * m.m33 - m.m13 * m.m31);
            mResult.m23 = -fInvDet * (m.m11 * m.m23 - m.m13 * m.m21);
            mResult.m24 =  0;
            mResult.m31 =  fInvDet * (m.m21 * m.m32 - m.m22 * m.m31);
            mResult.m32 = -fInvDet * (m.m11 * m.m32 - m.m12 * m.m31);
            mResult.m33 =  fInvDet * (m.m11 * m.m22 - m.m12 * m.m21);
            mResult.m34 =  0;
            mResult.m41 = -(m.m41 * mResult.m11 + m.m42 * mResult.m21 + m.m43 * mResult.m31);
            mResult.m42 = -(m.m41 * mResult.m12 + m.m42 * mResult.m22 + m.m43 * mResult.m32);
            mResult.m43 = -(m.m41 * mResult.m13 + m.m42 * mResult.m23 + m.m43 * mResult.m33);
            mResult.m44 =  1.0;

            return mResult;

        }
        template <typename T>
        matrix4x4<T> scaling(const vector3<T>& v)
        {
                return matrix4x4<T>(v.x,  0.0f, 0.0f, 0.0f,
                                    0.0f, v.y,  0.0f, 0.0f,
                                    0.0f, 0.0f, v.z,  0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f);
        }
        template <typename T>
        matrix4x4<T> frustum(const T left, const T right, const T bottom, 
                const T top, const T near, const T far)
        {
            matrix4x4<T> m = matrix4x4_identity<T>();
            m.n[0]  = 2 * near / (right - left);
            m.n[5]  = 2 * near / (top - bottom);
            m.n[8]  = (right + left) / (right - left);
            m.n[9]  = (top + bottom) / (top - bottom);
            m.n[10] = -(far + near) / (far - near);
            m.n[11] = -1;
            m.n[14] = -(2 * far * near) / (far - near);
            m.n[15] = 0;
            return m;
        }
        template <typename T>
        matrix4x4<T> perspective(const T fov, const T aspect, const T near, const T far)
        {
            T t = tan(fov/2 * DEG2RAD);
            return frustum<T>(-(t * aspect), (t * aspect), -(near * t), (near * t),
                   near, far);
    
        }
         template <typename T>
        matrix4x4<T> ortho(const T left, const T right, const T bottom, 
                const T top, const T near, const T far)
        {
            matrix4x4<T> m = matrix4x4_identity<T>();
            m.n[0]  = 2 / (right - left);
            m.n[5]  = 2 / (top - bottom);
            m.n[10] = -2 / (far - near);
            m.n[12] = -(right + left) / (right - left);
            m.n[13] = -(top + bottom) / (top - bottom);
            m.n[14] = -(far + near) / (far - near);
            return m;    
        }
    }
     template<typename T, typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
    inline std::basic_string<E, TAllocator, TStorage> mat4_string(const std::math::matrix4x4<T>& v, flags_t f = flags_t::dec  ) {   
            return v.to_string<E, TAllocator, TStorage>(); }


        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> mat4_string(const std::math::mat4f& v, flags_t f = flags_t::dec  ) {   
            return std::mat4_string<float, E, TAllocator, TStorage>(v); }

        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> mat4_string(const std::math::mat4d& v, flags_t f = flags_t::dec  ) {   
            return std::mat4_string<double, E, TAllocator, TStorage>(v); }
}

#endif /* MATRIX4X4_HPP */

