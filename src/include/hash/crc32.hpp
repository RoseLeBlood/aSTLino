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
 * File:   crc32.hpp
 * Author: annas
 *
 * Created on 4. Dezember 2016, 21:05
 */

#ifndef CRC32_HPP
#define CRC32_HPP
      
namespace std {
    
    template <uint32_t poly, uint32_t Tint = 0xFFFFFFFF>
    class crc32 {
    public:
        static constexpr uint32_t default_value = Tint;
        crc32() {
            createTable();
        }
        uint32_t hash(const void* data, size_t length, uint32_t oldcrc = Tint) {
           
            uint32_t crc = oldcrc;
            unsigned char* current = (unsigned char*) data;

            for(uint32_t i = 0; i < length; i++) {                
                crc = m_lookuptable[(crc ^ current[i]) & 0xFF] ^ (crc >> 8);
            }

            return ~crc; 
        }
         const char* get_name() { return "crc32"; }
    private:
         void createTable() {
            for (unsigned int i = 0; i < 256; i++) {
                uint32_t crc = i;
                for (unsigned int j = 0; j < 8; j++)
                    crc = (crc>>1) ^ (poly & (-(int)(crc & 1)));
                m_lookuptable[i] = crc;
            }
        }
    private:
        uint32_t m_lookuptable[256];
    };
    
}

#endif /* CRC32_HPP */

