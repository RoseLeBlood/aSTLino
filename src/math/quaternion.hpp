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
 * File:   quaternion.hpp
 * Author: annas
 *
 * Created on 12. November 2016, 23:50
 */

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "vector4.hpp"
#include "utils.hpp"

namespace std
{
    namespace math
    {
        template <typename T> class quaternion;
        typedef quaternion<float> quatf;
        typedef quaternion<double> quatd;
        typedef quaternion<int> quati;
        typedef quaternion<short> quats;
        
        template <typename T> 
        class quaternion : public object
        {
        public:
            typedef T value_type;
            typedef quaternion<T> self_type;
            
            union
            {
                struct
                {
                    vector3<value_type> v;
                    float               s;
		};
                vector4<value_type> vec;
		float qu[4];
            };
            
            virtual std::string to_string() {
                return vec.to_string();
            }
	    quaternion() : s(1.0f), v(vector3<value_type>(0.0f))	{}
	    quaternion(float _s, vector3<value_type> axis) : s(_s), v(axis) {} 
            quaternion(const vector3<value_type> &axis);
            quaternion(float fs, float x, float y, float z) : s(fs), v(vector3<value_type>(x,y,z))	{}
            quaternion(float *pfs)  : s(pfs[0]), v(vector3<value_type>(pfs[1],pfs[2],pfs[3]))	{}
            
            operator T*	() { return (T*)(qu); }
	    operator const T* () const	{ return (float*)qu; }

	    self_type& operator =  (const self_type& q)								
                { v = q.v; s = q.s; return *this; }
	    self_type& operator += (const self_type& q)								
                { v += q.v; s += q.s; return *this; }
	    self_type& operator -= (const self_type& q)								
                { v -= q.v; s -= q.s; return *this; }
	    self_type& operator *= (const self_type& b) {
                s =   ((s * b.s) - (v.x * b.v.x) - (v.y * b.v.z) - (v.z * b.v.z));
                v.x = ((s * b.v.x) + (v.x * b.s) + (v.y * b.v.y) - (v.z * b.v.y));
	        v.y = ((s * b.v.y) - (v.x * b.v.z) + (v.y * b.s) + (v.z * b.v.x));
	        v.z = ((s * b.v.z) + (v.x * b.v.y) - (v.y * b.v.x) + (v.z * b.s));
                return *this;
            }
	    self_type& operator *= (const value_type f)
                { s *= f; v.x *= f; v.y *= f; v.z *= f; return *this; }
	    self_type& operator /= (const self_type& q);   
	    self_type& operator /= (const value_type f)
                { s /= f; v.x /= f; v.y /= f; v.z /= f; return *this; }
        }; 
        
	
        template <typename T> 
        inline bool operator == (const quaternion<T>& a, const quaternion<T>& b)						
            { return ((a.v == b.v) && (a.s == b.s)); }
        template <typename T> 
	inline bool operator != (const quaternion<T>& a, const quaternion<T>& b)							
            { return !(a==b); }
        template <typename T> 
	inline bool operator <= (const quaternion<T>& a, const quaternion<T>& b)							
            { return ((a.v <= b.v) && (a.s <= b.s)); }
        template <typename T> 
	inline bool operator >= (const quaternion<T>& a, const quaternion<T>& b)							
            { return ((a.v >= b.v) && (a.s >= b.s)); }
        template <typename T> 
	inline bool operator < (const quaternion<T>& a, const quaternion<T>& b)							
            { return ((a.v < b.v) && (a.s < b.s)); }
        template <typename T> 
	inline bool operator > (const quaternion<T>& a, const quaternion<T>& b)							
            { return ((a.v > b.v) && (a.s > b.s)); }
         
        template <typename T> 
	inline quaternion<T> identy()														
            { return quaternion<T>(1.0f, 0.0f, 0.0f, 0.0f); }
        template <typename T> 
	inline T lenght(const quaternion<T>& v)											
            { return (T)sqrt((double)(v.s * v.s + v.v.x * v.v.x + v.v.y * v.v.y + v.v.z * v.v.z)); }
	template <typename T> 
        inline T lenghtSq(const quaternion<T>& v)										
            { return (v.s * v.s + (T)v.v.x * (T)v.v.x + (T)v.v.y * (T)v.v.y + (T)v.v.z * (T)v.v.z); }
        template <typename T>
        inline quaternion<T> invert(const quaternion<T> &q)
            {  T temp = lenghtSq(q); quaternion<T> tq = q;  tq.s /= temp; tq.v /= -temp; return q; }
        
        template <typename T>
        inline quaternion<T> exp(const quaternion<T>& v) {
            T Mul;
            quaternion<T> temp = v;
            T Length = lenght(temp.v);

	    if (Length > 1.0e-4) Mul = sin(Length)/Length;
	    else Mul = 1.0;

	    temp.s = cos(Length);

	    temp.v.x *= Mul;
	    temp.v.y *= Mul;
	    temp.v.z *= Mul;
            return temp;
        }
        template <typename T>
        inline quaternion<T> log(const quaternion<T>& v){
            T Length;
	    quaternion<T> temp = v;

            Length = lenght(temp.v);
            Length = atan(Length/temp.s);

            temp.s = 0.0;

            temp.v.x *= Length;
            temp.v.y *= Length;
            temp.v.z *= Length;

            return temp;
        }
        template <typename T>
        inline quaternion<T> normalize(const quaternion<T>& v) {
            T norme = lenght(v);
	    quaternion<T> temp = v;

            if (norme == 0.0) {
		temp.s = 1.0;
		temp.v = 0.0;
            } else {
		float recip = 1.0/norme;

		temp.s *= recip;
		temp.v.x *= recip;
		temp.v.y *= recip;
		temp.v.z *= recip;
            }
            return temp;
        }
        template <typename T>
        inline quaternion<T> conjugate(const quaternion<T>& v) {
            quaternion<T> temp = v;

            temp.s = -temp.s;
            temp.v = -temp.v;

            return temp;
        }
        template <typename T>
        inline quaternion<T> pow(const quaternion<T>& v, const T exp){
            if (fabs(v.s) > .9999)
                return v;
            
            T   alpha = acos(v.s);
            T   newAlpha = alpha * exp;
            quaternion<T> result;
            result.s = cos(newAlpha);

            float   mult = sin(newAlpha) / sin(alpha);
            result.v.x = (float)v.v.x * mult;
            result.v.y = (float)v.v.y * mult;
            result.v.z = (float)v.v.z * mult;

            return result;
        }
        template <typename T>
        inline T dot(const quaternion<T> &a, const quaternion<T> &b) {
            return a.s*b.s + a.v.x*b.v.x + a.v.y*b.v.y + a.v.z*b.v.z;
        }
        template <typename T>
        inline quaternion<T> power(const quaternion<T>& qu, T degree) {
                if ( degree == 0 ) return quaternion<T>((T)1.0, 0, 0, 0);
                quaternion<T> tmp_qu = qu ;

                for ( float f = 1 ; f < abs(degree) ; f++ )
                        tmp_qu *= qu ;

                if ( degree < 0 )
                    return ( 1.0f / tmp_qu );

                return tmp_qu ;
        }

        template <typename T>
        inline quaternion<T> sin(const quaternion<T> &q) {
            quaternion<T> s;

            for( T n = 0; n < (T)6.0; n++ )
		        s += (T)(::pow( -1.0 ,(double)n ) * (power( q , 2.0f * n + 1.0f ) ) /
                        ( factorial<T>( 2.0f * n + 1.0f ) ));

            return s ;
        }

        template <typename T>
        inline quaternion<T> cos(const quaternion<T> &q) {
            quaternion<T> s;

            for( T n = 1.0f; n <= 6.0f; n++ )
		s += ::pow( -1.0f ,n ) * power( q , 2.0f * n ) /
                        factorial<T>( 2.0f * n ) ;

            return s ;
        }
        template <typename T>
        inline quaternion<T> tan(const quaternion<T> &q) {
            if ( lenghtSq(q) == 0.0 ) return quaternion<T>(1, 0, 0, 0) ;
            return sin( q ) / cos( q ) ;
        }
        template <typename T>
        inline quaternion<T> ctan(const quaternion<T> &q)
        {
            if ( lenghtSq(q) == 0 ) return quaternion<T>(1.0, 0.0, 0.0, 0.0) ;
            return cos( q ) / sin( q ) ;
        }


        template <typename T>
        inline quaternion<T> operator * (const quaternion<T>& a,const quaternion<T>& b) {
                quaternion<T> q;
                q.s =   ((a.s * b.s) - (a.v.x * b.v.x) - (a.v.y * b.v.z) - (a.v.z * b.v.z));
                q.v.x = ((a.s * b.v.x) + (a.v.x * b.s) + (a.v.y * b.v.y) - (a.v.z * b.v.y));
	        q.v.y = ((a.s * b.v.y) - (a.v.x * b.v.z) + (a.v.y * b.s) + (a.v.z * b.v.x));
	        q.v.z = ((a.s * b.v.z) + (a.v.x * b.v.y) - (a.v.y * b.v.x) + (a.v.z * b.s));
                return q;
        } 
        template <typename T>
	inline quaternion<T> operator * (const quaternion<T>& a,const float b)
            { return quaternion<T>(a.s * b, a.v * b); }
	template <typename T>
	inline quaternion<T> operator + (const quaternion<T>& a,const quaternion<T>& b)
            { return quaternion<T>(a.s + b.s, a.v + b.v); }
        template <typename T>
	inline quaternion<T> operator - (const quaternion<T>& a,const quaternion<T>& b)
             { return quaternion<T>(a.s - b.s, a.v - b.v); }
        template <typename T>
	inline quaternion<T> operator - (const quaternion<T>& a)
            { return invert(a); }
        template <typename T>
	inline quaternion<T> operator / (const quaternion<T>& a,const quaternion<T>& b)
            { return a * invert(b); }
        template <typename T>
	inline quaternion<T> operator / (const quaternion<T>& a, const float b)
            { return quaternion<T>(a.s / b, a.v / b); }
        

        template <typename T>
        inline quaternion<T> quaternion_fromaxis(const float angle, vector3<T> axis)
        {
            T omega, s = lenght(axis), c;
	    quaternion<T> temp;
            vector3<T> vt = axis;

            if (fabs(s) > FLT_EPSILON)
            {
		c = 1.0f/s;
                vt *= c;

		omega = -0.5f * angle;
		s = (T)sin(omega);

		temp.v = vector3<T>(s*axis.x, s*axis.y, s*axis.z);
		temp.s = cos(omega);
            } else {
		temp.v = vector3<T>(0.0f);
		temp.s = 1;
            }
            return normalize(temp);
        }
		template <typename T>
        inline quaternion<T> quaternion_from(T yaw, T pitch, T roll) {
			quaternion<T> q;
			// Abbreviations for the various angular functions
			double cy = cos(yaw * 0.5);
			double sy = sin(yaw * 0.5);
			double cr = cos(roll * 0.5);
			double sr = sin(roll * 0.5);
			double cp = cos(pitch * 0.5);
			double sp = sin(pitch * 0.5);

			return quaternion<T>(cy * cr * cp + sy * sr * sp,
								 cy * sr * cp - sy * cr * sp,
			                     cy * cr * sp + sy * sr * cp,
			                     sy * cr * cp - cy * sr * sp);

		}
        template <typename T> 
        quaternion<T>::quaternion(const vector3<value_type> &axis) {
            value_type cos_z_2 = (value_type)cos(0.5*axis.z);
            value_type cos_y_2 = (value_type)cos(0.5*axis.y);
            value_type cos_x_2 = (value_type)cos(0.5*axis.x);

            value_type sin_z_2 = (value_type)sin(0.5*axis.z);
            value_type sin_y_2 = (value_type)sin(0.5*axis.y);
            value_type sin_x_2 = (value_type)sin(0.5*axis.x);

            // and now compute quaternion
            s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
            v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
            v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
            v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
        }
        template <typename T>
        quaternion<T>& quaternion<T>::operator /= (const quaternion<T>& q) {
            (* this) *= invert(q); return *this;
        }

    }
}

#endif /* QUATERNION_HPP */

