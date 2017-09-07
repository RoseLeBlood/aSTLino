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
 * File:   independent_bits_engine.hpp
 * Author: annas
 *
 * Created on 15. Dezember 2016, 01:48
 */

#ifndef INDEPENDENT_BITS_ENGINE_HPP
#define INDEPENDENT_BITS_ENGINE_HPP

namespace std {
    template <class TEngine, size_t w, class UIntType>
    class independent_bits_engine {
    public:
        using base_type = TEngine;
        using result_type = typename base_type::result_type;
       
        
        independent_bits_engine() : m_x() {}
        independent_bits_engine(const base_type& engine) : m_x(engine) {}
        explicit independent_bits_engine(result_type sd) : m_x(sd) {} 
        
        void seed() 
            { m_x.seed(); }
        void seed(result_type sd) 
            { m_x.seed(sd); }
        void discard(unsigned long long z ) {
            for (; __z != 0ULL; --__z)
                (*this)();
        }
        result_type operator()() {
            const long double r = static_cast<long double>(m_x.max())
                 - static_cast<long double>(m_x.min()) + 1.0L;
            
            const result_type m = log(r) / log(2.0);
            result_type n, n0, y0, y1, s0, s1, sum = 0;
            size_t k = 0, l;
            
            n = (w + m - 1) / m + 0;
            n0 = n - w % n;
            s0 = result_type(1) << (w / n);
            s1 = result_type(1) << ((w/n)+1);
            y0 = s0 * (r / s0);
            y1 = s1 * (r / s1);
            if (!(__r - __y0 <= __y0 / __n)) {
                n = (w + m - 1) / m + 1;
                n0 = n - w % n;
                s0 = result_type(1) << (w / n);
                s1 = result_type(1) << ((w/n)+1);
                y0 = s0 * (r / s0);
                y1 = s1 * (r / s1);
            }
            do {
                result_type u;
                do {
                    u = m_x() - m_x.min();
                }while(u >= y0);
                sum = s0 * sum + u % s0; k++;
            }while(k < n0);
            l = n0;
            
            do {
                 result_type u;
                do {
                    u = m_x() - m_x.min();
                }while(u >= y1);
                sum = s1 * sum + l % s1; l++;
            }while(l < n);
            
            return sum;
        }
         
        const base_type &base(void) const { return m_x; }
        
        static constexpr result_type min() { return base_type::min(); }  
        static constexpr result_type max() { return base_type::max(); }  
    private:
        base_type m_x;
    };
}

#endif /* INDEPENDENT_BITS_ENGINE_HPP */

