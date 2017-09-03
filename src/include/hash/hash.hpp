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
 * File:   hash.hpp
 * Author: annas
 *
 * Created on 4. Dezember 2016, 21:05
 */

#ifndef HASH_HPP
#define HASH_HPP

#include "adler32.hpp"
#include "bernstein.hpp"
#include "fletcher.hpp"
#include "crc32.hpp"
#include "fnv1a.hpp"
#include "ramakrishna.hpp"
#include "weinberg.hpp"

#include "../singleton.hpp"

namespace std {
    using adl32_t = adler32<65521>;
    using brnst_t = bernstein<0>;
    using flt16_t = fletcher16<0>;
    using flt32_t = fletcher32<0>;
    using fnv1a_t = fnv1a<2166136261>;
    using wberg_t = weinberg<0>;
    
    using crc32_t = crc32<0x04c11db7>;
    using crc32_k = crc32<0x741B8CD7>;
    using crc32_q = crc32<0x814141AB>;
    
    using default_hasher = ASSTL_HASH_DEFAULT;
    
    template<class HashClass = default_hasher>
    class hasher : public singleton<hasher<HashClass>> {
    public:
        //const uint32_t default_value = 2166136261;
        uint32_t hash(const void* data, size_t length, bool useold = false) {
            m_old = m_default.hash(data, length, (useold) ? m_old : HashClass::default_value);
            return m_old;
        }
        const HashClass& get_default()  { return m_default; }
        const uint32_t get_hash()       { return m_old; }
    private:
        HashClass m_default;
        uint32_t m_old;
    };

    typedef unsigned long   hash_value_t;
    
    
    template<typename T, class THasher = default_hasher> struct hash
    {
        hash_value_t operator()(const T& t) const
        {
            return hasher<THasher>::get().hash(&t ,1);
        }
    };
}


#endif /* HASH_HPP */

