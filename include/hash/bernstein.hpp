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
 * File:   bernstein.hpp
 * Author: annas
 *
 * Created on 7. Dezember 2016, 01:24
 */

#ifndef BERNSTEIN_HPP
#define BERNSTEIN_HPP

namespace std {
    template <uint32_t T>
    class bernstein {
    public:
        static constexpr uint32_t default_value = 5381;
        
        uint32_t hash(const char* data, size_t length, uint32_t old = 5381) {
           uint32_t hash = old;
           for(uint32_t i = 0; i < length; ++i)
               hash = 33 * hash + data[i];
           return hash ^ (hash >> 16);
        }
         const char* get_name() { return "bernstein"; }
    };
}

#endif /* BERNSTEIN_HPP */

