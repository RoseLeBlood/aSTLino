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
 * File:   physik.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 22:39
 */

#ifndef PHYSIK_HPP
#define PHYSIK_HPP

#include "ext.hpp"

namespace std
{
    namespace math
    {
        template <typename T = double>
        class physik;
        template <typename T = double>
        class physik_base;
        
        typedef physik<float> physiksystem;
        typedef physik_base<float> physiksystem_base;
        
        typedef physik<double> physiksystemEx;
        typedef physik_base<double> physiksystem_baseEx;
        
        template <typename T = double>
        class physik_base
        {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef physik_base<T> self_type;
            
	    virtual void update(value_type fTime, value_type fRunTime) = 0;
            
            virtual matrix4x4<T> getWorldMatrix() = 0;
            virtual void setWorldMatrix(const matrix4x4<T>& p);
            virtual value_type getBoundingsphereRadius() { return 1; }
        };
        template <typename T = double>
        class physik : public object
        {
        public:
            typedef physik_base<T> physik_value;
            typedef T value_type;
            typedef T* pointer;
            
            typedef physik<T> self_type;
            
            
            physik(physik_value *o) :
		m_Velocity(0,0,0), m_Accelerate(0,0,0), m_AngularAccelerate(0,0,0), m_AngularVelocity(0,0,0)
            {
                    m_pRender = o;
                    m_Translation = matrix4x4_identity();
                    m_Rotation = matrix4x4_identity();
                    m_Scaling = scaling(vector3<T>(m_pRender->getWorldMatrix()->m11,  m_pRender->getWorldMatrix()->m22,
                                                          m_pRender->getWorldMatrix()->m33));
                    m_Mass = 1;
            }

	    physik(physik_value* o, const vector3<T>& Position,
		   const vector3<T>& Velocity, const vector3<T>& Accelerator, 
                   T mass = 1.0) :
                    m_Velocity(Velocity), m_Accelerate(Accelerator), m_AngularVelocity(0,0,0), m_AngularAccelerate(0,0,0)
            {
                    m_pRender = o;
                    m_Translation = translate(matrix4x4_identity(), Position);
                    m_Rotation = matrix4x4_identity();
                    m_Scaling = scaling(vector3<T>(m_pRender->getWorldMatrix()->m11,
                                                          m_pRender->getWorldMatrix()->m22,
                                                         m_pRender->getWorldMatrix()->m33));
                    m_Mass = mass;
            }

	    virtual void update(value_type fTime, value_type fRunTime);
            void reset();
            
	    void accelerate(const vector3<T>& accel)
            {
		m_Accelerate = transformnormal(accel, m_pRender->getWorldMatrix());
            }
	    void angaccel(vector3<T> accel)
            {
		m_AngularAccelerate = transformnormal(accel, m_pRender->getWorldMatrix());
            }

            void set_accelerate(vector3<T> Acc)
                {  m_Accelerate= Acc; }
	    void set_angaccel(vector3<T> Ang)
                { m_AngularAccelerate = Ang; }
	    
	    vector3<T>	position()
                { return transformcoord(vector3<T>(0), m_Translation); }
	    vector3<T>	velocity()
                { return m_Velocity; }
	    value_type	mass()
                { return m_Mass; }
	    value_type	getBoundingsphereRadius()
                { return m_pRender->getBoundingsphereRadius(); }

	    void set_velocity(vector3<T> velo)
                { m_Velocity = velo; }
            virtual std::string to_string() {
                std::frmstring("[physik] pos: %s vel: %s\nmass: %.3f bsradius: %.3f", 
                       position().to_string() , velocity().to_string(),
                       mass,  getBoundingsphereRadius);
            }
	private:
	    matrix4x4<T>        m_Translation;
	    vector3<T>		m_Velocity;
	    vector3<T>		m_Accelerate;

	    matrix4x4<T>  	m_Rotation;
	    vector3<T>		m_AngularVelocity;
	    vector3<T>		m_AngularAccelerate;

	    matrix4x4<T>  	m_Scaling;
	    value_type		m_Mass;

	    physik_value	*m_pRender;
	
        };
        template <typename T = double>
        void physik::update(value_type fTime, value_type fRunTime)
        {
            float angle = fTime * lenghtSq(m_AngularAccelerate);
	    vector3<T> axis = normalize(m_AngularVelocity);
            
            if(m_pRender)
            {
		matrix4x4<T> mWorld = matrix4x4_identity(), m = matrix4x4_identity();
                m_Rotation = rotate(m_Rotation, axis, angle);
		m_Translation = translate(m_Translation, scale(m_Velocity, fTime));
                
		m = m_Scaling * m_Rotation;
		mWorld = m * m_Translation;

		m_pRender->setWorldMatrix(mWorld);
	    }
	    m_Velocity += fTime * m_Accelerate;
	    m_AngularVelocity += fTime * m_AngularAccelerate;		
        }
        template <typename T = double>
        void physik::reset()
        {
            m_Accelerate = vector3<T>(0);
            m_AngularAccelerate = vector3<T>(0);
            m_AngularVelocity = vector3<T>(0);
            m_Velocity = vector3<T>(0);
        }
        
        template <typename T>
        bool is_physikcollision(physik<T> *p1, physik<T> *p2)
        {
            vector3<T> dist;
	    dist = p1->position() - p2->position();
            bool col = lenght(dist) <= p1->getBoundingsphereRadius() + p2->getBoundingsphereRadius();
            if(col)
	    {
		vector3<T> v1 = p1->velocity();
		vector3<T> v2 = p2->velocity();
                
                T m1 = p1->mass();
		T m2 = p2->mass();

		vector3<T> v1New, v2New, a, n, b;
                a = normalize(dist);
                n = cross(v1, v2);
                
		if(n.x == n.y && n.x == n.z && n.x == 0.0f) {
		    v1New = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
		    v2New = ((m2 - m1) * v2 + 2  * m1 * v1) / (m1 + m2);
		} else 	{
                    n = normalize(n);
		    b = cross(n, a);

		    T ab = dot(a, b);
		    T v11 = (dot(v1, a) - dot(v1, b) * ab) / ( 1 - ab * ab);
		    T v12 = (dot(v1, b) - dot(v1, a) * ab) / ( 1 - ab * ab);
                    T v21 = (dot(v2, a) - dot(v2, b) * ab) / ( 1 - ab * ab);
		    T v22 = (dot(v2, b) - dot(v2, a) * ab) / ( 1 - ab * ab);

		    v1New = a * ((m1 - m2) * v11 + 2 * m2 * v21) / (m1 + m2) + b * v12;
		    v2New = a * ((m2 - m1) * v21 + 2 * m1 * v11) / (m1 + m2) + b * v22;
		}
                p1->set_velocity(v1New);
		p2->set_velocity(v2New);	
           }
           return col;
        }
    }
}

#endif /* PHYSIK_HPP */

