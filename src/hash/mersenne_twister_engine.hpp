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
 * File:   mersenne_twister_engine.hpp
 * Author: annas
 *
 * Created on 14. Dezember 2016, 23:42
 */

#ifndef MERSENNE_TWISTER_ENGINE_HPP
#define MERSENNE_TWISTER_ENGINE_HPP

namespace std 
{
    template <typename UIntType, size_t w, size_t n, size_t m, size_t r,
          UIntType a, size_t u, UIntType d, size_t s,
          UIntType b, size_t t,
          UIntType c, size_t l, UIntType f>
    class mersenne_twister_engine
    {
    public:
        using result_type = UIntType;
        static constexpr size_t word_size = w;
        static constexpr size_t state_size = n;
        static constexpr size_t shift_size = m;
        static constexpr size_t mask_bits = r;
        static constexpr result_type xor_mask = a;
        static constexpr size_t tempering_u = u;
        static constexpr result_type tempering_d = d;
        static constexpr size_t tempering_s = s;
        static constexpr result_type tempering_b = b;
        static constexpr size_t tempering_t = t;
        static constexpr result_type tempering_c = c;
        static constexpr size_t tempering_l = l;
        static constexpr result_type initialization_multiplier = f;
        static constexpr size_t MASK_LOWER = (1ull << mask_bits) - 1;
        static constexpr size_t MASK_UPPER = (1ull << mask_bits);
        static constexpr result_type default_seed = 5489u;
        
        explicit mersenne_twister_engine(result_type sd = default_seed) {
            seed(sd);
        }
        void seed(result_type sd = default_seed) {
            m_state[0] = seed;
            m_index = state_size;
            for (uint32_t i = 1; i < state_size; i++ ) {
                m_state[i] = (initialization_multiplier * (m_state[i - 1] ^ (m_state[i - 1] >> 30)) + i);
            }
        }
        result_type operator()() {
            uint32_t  y;
            int i = m_index;
            if ( m_index >= state_size ) {
                twist();
                i = m_index;
            }
            y = m_state[i];
            m_index = i + 1;

            y ^= (m_state[i] >> tempering_u);
            y ^= (y << tempering_s) & tempering_b;
            y ^= (y << tempering_t) & tempering_c;
            y ^= (y >> tempering_l);
            
            m_y = y;
            return y;
        }  
        void discard(unsigned long long z) {
            for (; z != 0ULL; --z)
                (*this).operator ()();
        } 
        result_type last() {
            return m_y;
        }
        static constexpr result_type min() { return 0; }  
        static constexpr result_type max() { return 2 ^ word_size - 1; }  
    private:
        void twist() {
            result_type  i, x, xA;
            for ( i = 0; i < state_size; i++ ){
                x = (m_state[i] & MASK_UPPER) + (m_state[(i + 1) % state_size] & MASK_LOWER);
                xA = x >> 1;
                if ( x & 0x1 )
                    xA ^= xor_mask;

                m_state[i] = m_state[(i + shift_size) % state_size] ^ xA;
            }
            m_index = 0;
        }
    private:
        result_type   m_state[state_size+1]; 
        uint16_t      m_index;
        result_type   m_y;   
    };
}


#endif /* MERSENNE_TWISTER_ENGINE_HPP */

