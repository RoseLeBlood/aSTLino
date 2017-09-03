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
 * File:   fletcher.hpp
 * Author: annas
 *
 * Created on 7. Dezember 2016, 01:53
 */

#ifndef FLETCHER_HPP
#define FLETCHER_HPP


namespace std {
    template <uint32_t T>
    class fletcher32 {
    public:
        static constexpr uint32_t default_value = 0;
        
        uint32_t hash(const void* data, size_t length, uint32_t old = 0) {
           uint32_t sum1 = 0xffff, sum2 = 0xffff;
           size_t tlen;
 
           while (length) {
                tlen = ((length >= 359) ? 359 : length);
                length -= tlen;
                do {
                        sum2 += sum1 += *data++;
                        tlen--;
                } while (tlen);
                sum1 = (sum1 & 0xffff) + (sum1 >> 16);
                sum2 = (sum2 & 0xffff) + (sum2 >> 16);
            }
            sum1 = (sum1 & 0xffff) + (sum1 >> 16);
            sum2 = (sum2 & 0xffff) + (sum2 >> 16);
            return (sum2 << 16) | sum1;      
        }
         const char* get_name() { return "fletcher32"; }
    };
    
    template <uint32_t T>
    class fletcher16 {
    public:
        const uint32_t default_value = 0;
        
        uint16_t hash(const void* data, size_t length, uint32_t old = 0) {
           uint32_t sum1 = 0xff, sum2 = 0xff;
           size_t tlen;
 
           while (length) {
                tlen = ((length >= 20) ? 20 : length);
                length -= tlen;
                do {
                        sum2 += sum1 += *data++;
                        tlen--;
                } while (tlen);
                sum1 = (sum1 & 0xff) + (sum1 >> 8);
                sum2 = (sum2 & 0xff) + (sum2 >> 8);
            }
            sum1 = (sum1 & 0xff) + (sum1 >> 8);
            sum2 = (sum2 & 0xff) + (sum2 >> 8);
            return (sum2 << 16) | sum1;      
        }
         const char* get_name() { return "fletcher16"; }
    };
}

#endif /* FLETCHER_HPP */

