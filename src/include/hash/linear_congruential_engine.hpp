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
 * File:   linear_congruential_engine.hpp
 * Author: annas
 *
 * Created on 14. Dezember 2016, 22:32
 */

#ifndef LINEAR_CONGRUENTIAL_ENGINE_HPP
#define LINEAR_CONGRUENTIAL_ENGINE_HPP

namespace std 
{
    template <typename TIntType, TIntType a, TIntType c, TIntType m>
    class linear_congruential_engine {
    public:
        using result_type = TIntType;
        static constexpr result_type multiplier = a;
        static constexpr result_type increment = c;  
        static constexpr result_type modulus = m; 
        static constexpr result_type default_seed = 1u; 
        
        explicit linear_congruential_engine(result_type s = default_seed)
            : m_iX(s % modulus) {}
        
        void seed(result_type s = default_seed) {
            m_iX = s % modulus;
        }
        void discard(unsigned long long z) {
            for (; z != 0ULL; --z)
                (*this).operator ()();
        } 
        result_type last() {
            return m_iX;
        }
        result_type operator()() {
            m_iX = ( multiplier * m_iX + increment) % modulus;
            return m_iX;
        }  
        static constexpr result_type min() { return c == 0u ? 1u: 0u; }  
        static constexpr result_type max() { return m - 1u; }  
    private:
        result_type m_iX;
    };
    template <class UIntType, UIntType a, UIntType c, UIntType m>
    bool operator == ( const linear_congruential_engine<UIntType,a,c,m>& lhs,
                      const linear_congruential_engine<UIntType,a,c,m>& rhs ) {
        if(lhs.multiplier != rhs.multiplier) return false;
        if(lhs.increment != rhs.increment) return false;
        if(lhs.modulus != rhs.modulus) return false;
        return true;
    }
    template <class UIntType, UIntType a, UIntType c, UIntType m>
    bool operator!= ( const linear_congruential_engine<UIntType,a,c,m>& lhs,
                  const linear_congruential_engine<UIntType,a,c,m>& rhs ) {
        return !(lhs == rhs);      
    }
}


#endif /* LINEAR_CONGRUENTIAL_ENGINE_HPP */

