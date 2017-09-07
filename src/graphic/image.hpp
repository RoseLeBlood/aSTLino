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
 * File:   image.hpp
 * Author: annas
 *
 * Created on 6. Dezember 2016, 21:33
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "../common.hpp"
#include "../math/vector4.hpp"
#include "../math/colors.hpp"
#include "../property.hpp"
#include "../filestream.hpp"

namespace std
{
    namespace graphic
    {
        template <typename T, std::math::color<T> BC = std::math::colors_base<T>::Navy>
        class image
        {
        public:
            using color_type =  std::math::color<T>;
            using basic_color = BC;
            using self_type = image<T, BC>;
            using size_type = std::math::vector2<int>;
            
            std::prop_t<std::string> Name;
            
            image()  {
                create(size_type(32,32), BC);
            }
            image(std::string name, size_type size) {
               create(size, BC);
               Name = name;
            }
            image(std::string name, size_type size, stream* str) {
                Name = name;
                create(size, BC);
                auto x = std::_min<int>( (m_vecSize.x * m_vecSize.y *4),
                        str->size() );
                unsigned char colorBlock[4];
                for (int i = 0; i < x; i++) {
                    
                    if (str->read(colorBlock, 0, 4) == 4)
			m_imgData[i] = color_type(  colorBlock[0], 
                                                    colorBlock[1], 
                                                    colorBlock[2],
                                                    colorBlock[3]);
		}	
            }
            ~image() {
                if(m_imgData) { delete m_imgData; }
            }
            void setpixel(size_type pos, color_type col ) {
                if(pos.x < m_vecSize.x && pos.y < m_vecSize.y ) {
                    m_imgData[ pos.x + pos.y * m_vecSize.x] = col;
                } 
            }
            color_type& getpixel(size_type pos) {
                if(pos.x < m_vecSize.x && pos.y < m_vecSize.y ) {
                    return m_imgData[ pos.x + pos.y * m_vecSize.x];
                }
            }
            color_type* get() {
                return m_imgData;
            }
            color_type& operator [](size_type pos) {
                 return getpixel(pos);
            }
        protected:
            void create(size_type size, color_type color ) {
               m_imgData = new color_type[size.x * size.y]; 
               #pragma openmp
               for(int i = 0; i < size.x * size.y; i++) {
                   m_imgData[i] = basic_color;
               }  
            }
        private:
            color_type* m_imgData;
            size_type m_vecSize;
        };
    }
}

#endif /* IMAGE_HPP */

