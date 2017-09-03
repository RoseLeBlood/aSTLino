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
 * File:   boundingsphere.hpp
 * Author: annas
 *
 * Created on 25. November 2016, 01:47
 */

#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"

namespace std 
{
    namespace math 
    {
        template<typename T>
	class ray : public object
        {
        public:
            typedef ray<T> self_type;
            typedef T value_type;
            typedef T* pointer;
            
            ray (vector3<value_type> position, vector3<value_type> direction)
	    {
		m_position = position;
		m_directon = direction;
            }
	    ray(const ray<value_type>& other)
            {
                m_position = other.m_position;
                m_directon = other.m_directon;
            }
            const vector3<value_type>& position() { return m_position; }
            void position(const vector3<value_type>& p) { m_position = p; }
            
            const vector3<value_type>& direction() { return m_directon; }
            void direction(const vector3<value_type>& p) { m_directon = p; }
            
            virtual std::string to_string() {
                std::frmstring("[ray] pos: %s dir: %s", m_position.to_string().c_str(),
                        m_directon.to_string().c_str());
            }
        private:
            vector3<T> m_position;
            vector3<T> m_directon;
            
        };
        template <typename T>
        inline bool operator == (ray<T> a, ray<T> b)
        {
            return a.direction() == b.direction() &&
                    a.position() == b.position();
        }
        template <typename T>
        inline bool operator != (ray<T> a, ray<T> b)
        {
            return a.direction() != b.direction() &&
                    a.position() != b.position();
        }
    }
}

#endif /* BOUNDINGSPHERE_HPP */

