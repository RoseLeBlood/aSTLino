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
 * File:   discard_block_engine.hpp
 * Author: annas
 *
 * Created on 15. Dezember 2016, 01:24
 */

#ifndef DISCARD_BLOCK_ENGINE_HPP
#define DISCARD_BLOCK_ENGINE_HPP

namespace std 
{
    template <class TEngine, size_t p, size_t r>
    class discard_block_engine {
    public:
        using base_type = TEngine;
        using result_type = typename TEngine::result_type;
        
        static const size_t block_size = p;
        static const size_t used_block = r;
        
        discard_block_engine() 
            : m_e(), m_n(0) {}
        explicit discard_block_engine(const base_type &bt)
            : m_e(bt), m_n(0) {}
        explicit discard_block_engine(result_type s)
            : m_e(s), m_n(0) {}
        
        void seed(result_type s) {
            m_e.seed(s);
            m_n = 0;
        }
        void seed() {
            m_e.seed();
            m_n = 0;
        }
        
        result_type operator()(void) {
             if(m_n >= used_block) {
                m_e.discard(block_size - m_n);
                m_n = 0;
            }
            ++m_n;
            return m_e();
        }
        void discard(unsigned long long z) {
           for(; z > 0; --z) 
                this->operator()();
        }
        
        const base_type &base(void) const { return m_e; }
    private:
        base_type m_e;
        unsigned int m_n;
    };
}

#endif /* DISCARD_BLOCK_ENGINE_HPP */

