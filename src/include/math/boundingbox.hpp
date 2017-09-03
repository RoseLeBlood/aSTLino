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
 * File:   boundingbox.hpp
 * Author: annas
 *
 * Created on 25. November 2016, 00:14
 */

#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "vector4.hpp"

namespace std
{
    namespace math
    {
        /// @brief enum 
        typedef enum boundingcontains
        {
            Disjoint, 
            Contains,
            Intersects
        }contains_t;
        
        template<typename T>
	class boundingbox;
        
        /// @brief bbox is a float boundingbox type
        typedef boundingbox<float>  bbox;
        /// @brief dbox is a double boundingbox type
        typedef boundingbox<double> dbox;
        
        ///@brief a clasd for a BoundingBox 
        //@tparam T description type @see bbox @see dbox
        template<typename T>
	class boundingbox
        {
        public:
            using self_type = boundingbox<T>;
            using value_type = T;
            using pointer = T*;
            const int CornerCount = 8;
            
            /// @brief create the BoundingBox from max and min type 
            boundingbox (vector3<T> min, vector3<T> max) {
		m_vMin = min;
		m_vMax = max;
            }
            /// @brief contain the other box this box
            /// @param box The other box
            /// @return @see boundingcontains
            contains_t contains(const boundingbox<T>& box) {
                if ((m_vMax.x < box.m_vMin.x || m_vMin.x > box.m_vMax.x) ||
		   (m_vMax.y < box.m_vMin.y || m_vMin.y > box.m_vMax.y) ||
		   (m_vMax.z < box.m_vMin.z || m_vMin.z > box.m_vMax.z)) {
			return contains_t::Disjoint;
		}
                if ((m_vMin.x <= box.m_vMin.x && m_vMax.x >= box.m_vMax.x) &&
		   (m_vMin.y <= box.m_vMin.y && m_vMax.y >= box.m_vMax.y) &&
		   (m_vMin.z <= box.m_vMin.z && m_vMax.z >= box.m_vMax.z)) {
			return contains_t::Contains;
                }
                return contains_t::Intersects;
            }
            /// @brief cheak of the point contains this class
            /// @param point The to cheaked point
            /// @return @see boundingcontains
            contains_t contains (vector3<T> point)
            {
		if ((m_vMin.x <= point.x && m_vMax.x >= point.x) &&
                    (m_vMin.y <= point.y && m_vMax.y >= point.y) &&
                    (m_vMin.z <= point.z && m_vMax.z >= point.z)) {
                    return contains_t::Contains;
		}
		return contains_t::Disjoint;
            }
            /// @brief get the corners of this box
            /// @param corners the out array
            void getcorners (vector3<T> corners[CornerCount])
	    {
		corners[0] = vector3<T> (m_vMin.x, m_vMax.y, m_vMax.z);
		corners[1] = vector3<T> (m_vMax.x, m_vMax.y, m_vMax.z);
		corners[2] = vector3<T> (m_vMax.x, m_vMin.y, m_vMax.z);
		corners[3] = vector3<T> (m_vMin.x, m_vMin.y, m_vMax.z);
		corners[4] = vector3<T> (m_vMin.x, m_vMax.y, m_vMin.z);
		corners[5] = vector3<T> (m_vMax.x, m_vMax.y, m_vMin.z);
		corners[6] = vector3<T> (m_vMax.x, m_vMin.y, m_vMin.z);
		corners[7] = vector3<T> (m_vMin.x, m_vMin.y, m_vMin.z);
            }
            /// @brief cheak of intersect the other box this box
            /// @param box The other box
            /// @return true when this box contains the other box
            bool Intersects (const boundingbox<T>& box)
	    {
		return contains (box) == contains_t::Intersects;
	    }
           
            self_type& operator =  (const self_type& v)	{ 
                m_vMin = m_vMin; m_vMax = v.m_vMax; return *this; } 
            
            vector3<T> getmin() { return m_vMin; }
            vector3<T> getmax() { return m_vMax; }
            
            
            virtual std::string to_string() {
                std::frmstring("[bbox] Min: %s  Max: %s", std::to_string(m_vMin), 
                        std::to_string(m_vMax) );
            }
        private:
            vector3<T> m_vMin;
            vector3<T> m_vMax;
        };
        template < typename T >
        bool operator == (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() == b.getmin() && a.getmax() == b.getmax();
        }
        template < typename T >
	bool operator != (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() != b.getmin() && a.getmax() != b.getmax();
        }
        template < typename T >
	bool operator <= (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() <= b.getmin() && a.getmax() <= b.getmax();
        }
        template < typename T >
	bool operator >= (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() >= b.getmin() && a.getmax() >= b.getmax();
        }
        template < typename T >
	bool operator > (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() > b.getmin() && a.getmax() > b.getmax();
        }
        template < typename T >
	bool operator < (const boundingbox<T>& a, const boundingbox<T>& b) {
                return a.getmin() < b.getmin() && a.getmax() < b.getmax();
        }
    }
}

#endif /* BOUNDINGBOX_HPP */

