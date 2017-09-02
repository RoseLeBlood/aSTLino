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
 * File:   shuffle_order_engine.hpp
 * Author: annas
 *
 * Created on 15. Dezember 2016, 02:32
 */

#ifndef SHUFFLE_ORDER_ENGINE_HPP
#define SHUFFLE_ORDER_ENGINE_HPP

namespace std {
    template <class TEngine, size_t k> 
    class shuffle_order_engine {
    public:
        using base_type = TEngine;
        using result_type = typename base_type::result_type;
        
        static constexpr size_t table_size = k;
        
        shuffle_order_engine() : m_x() { init(); }
        explicit shuffle_order_engine (const base_type& e) : m_x(e)  { init(); }
        explicit shuffle_order_engine (base_type&& e) : m_x(e)  { init(); }
        explicit shuffle_order_engine (result_type val) : m_x(val)  { init(); }
        
        void seed() { m_x.seed(); init(); }
        void seed(result_type sd) { m_x.seed(sd); init(); }
   
        result_type operator()() {
            size_t j = table_size * ((m_y - min()) / ((max() - min()) +1 ));
            m_y = m_stored[j];
            m_stored[j] = m_x();
            return m_y;
        }
        void discard(unsigned long long z) {
            for (; z != 0ULL; --z)
                (*this).operator ()();
        }

        static constexpr result_type min() { return base_type::min(); }
        static constexpr result_type max() { return base_type::max(); }
    
        const base_type& base() const { return m_x; }
    private:
        void init() {
            for(size_t i = 0; i < table_size; ++i) {
                m_stored[i] = m_x();
                m_y = m_x();
            }
        }
    private:
        base_type m_x;
        result_type m_stored[table_size];
        result_type m_y;
    };
}

#endif /* SHUFFLE_ORDER_ENGINE_HPP */

