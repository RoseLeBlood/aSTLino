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
 * File:   subtract_with_carry_engine.hpp
 * Author: annas
 *
 * Created on 14. Dezember 2016, 22:29
 */

#ifndef SUBTRACT_WITH_CARRY_ENGINE_HPP
#define SUBTRACT_WITH_CARRY_ENGINE_HPP


namespace std
{
    namespace internal {
        template<typename Tp, Tp m, Tp a, Tp c, bool s>
        struct _mod<Tp, m, a, c, true, s> {
            static Tp calc(Tp x) {
                Tp res = a * x + c;
                if (m) res %= m; 
                return res;
            }
        };
        template<typename Tp, Tp m, Tp a = 1, Tp c = 0>
        inline Tp mod(Tp x) { return mod<Tp, m, a, c>::calc(x); }
    }
    template<class UIntType, size_t word_size, size_t short_lag, size_t long_lag>
    class subtract_with_carry_engine 
    {
    public:
        using result_type = UIntType;
        static constexpr size_t default_seed = 19780503u;
        
        subtract_with_carry_engine(size_t sd = default_seed) {
            seed(sd);
        } 
        
        void seed(size_t sd = default_seed) {
            linear_congruential_engine<result_type, 
                    40014u, 0u, 2147483563u> e(sd == 0u ? default_seed : sd);
            
            result_type mds = (UIntType(1) << word_size);
            for(size_t i = 0; i < long_lag; ++i)
                m_x[i] = internal::mod<result_type, 1, 0, mds>(e());
            m_carry = (m_x[long_lag-1] == 0);
            m_p = 0; 
        }
        void discard(unsigned long long z) {
            for (; z != 0ULL; --z)
                (*this).operator ()();
        } 
        result_type last() {
            return m_xlast;
        }
        result_type operator()() {
            int short_index = m_p - short_lag;
            short_index += (short_index < 0) ? long_lag : 0;
            if (m_x[short_index] >= m_x[m_p] + m_carry) {
                m_xlast =  m_x[short_index] - m_x[m_p] - m_carry;
                m_carry = 0;
            } else {
                m_xlast = modulus - m_x[m_p] - m_carry + m_x[short_index];
                m_carry = 1;
            }
            m_x[m_p] = m_xlast; ++m_p;
            if(m_p >= long_lag)
                m_p = 0;
            return m_xlast;
        }  
        static constexpr result_type min() { return 0; }  
        static constexpr result_type max() { return (UIntType(1) << word_size) - 1; }  
    private:
        result_type m_carry;
        result_type m_x[long_lag];
        size_t m_p;
        result_type m_xlast;
    };
    
  
}

#endif /* SUBTRACT_WITH_CARRY_ENGINE_HPP */

