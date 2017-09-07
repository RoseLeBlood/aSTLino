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
 * File:   crc16.hpp
 * Author: annas
 *
 * Created on 4. Dezember 2016, 21:05
 */

#ifndef CRC16_HPP
#define CRC16_HPP
      
namespace std {
    
    template <uint32_t POLY = 0xA001, uint32_t Tint = 0x90F1>
    class crc16 {
    public:
        static constexpr uint32_t default_value = Tint;
        crc16() {
          
        }
        uint32_t hash(const void* data, size_t length, uint32_t oldcrc = Tint) {
           
            uint32_t crc = oldcrc;
            unsigned char* current = (unsigned char*) data;
            while (length--) {
        	crc ^= *current++;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        	crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
             }
    	     return crc;
        }
        const char* get_name() { return "crc16"; }
    private:
        unsigned long m_lookuptable[16];
    };
    
}

#endif /* CRC32_HPP */

