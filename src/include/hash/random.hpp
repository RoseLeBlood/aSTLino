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
 * File:   random.hpp
 * Author: annas
 *
 * Created on 10. Dezember 2016, 23:17
 */

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "../string.hpp"
#include "linear_congruential_engine.hpp"
#include "subtract_with_carry_engine.hpp"
#include "mersenne_twister_engine.hpp"
#include "discard_block_engine.hpp"
#include "shuffle_order_engine.hpp"
#include "isaac_engine.hpp"



namespace std {
    using minstd_rand0 = linear_congruential_engine<uint_fast32_t, 16807, 0, 2147483647>;
    using minstd_rand = linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>;
    
    using mt19937 = mersenne_twister_engine<uint_fast32_t,
                    32,624,397,31,0x9908b0df,
                    11,0xffffffff,
                     7,0x9d2c5680,
                    15,0xefc60000,
                    18,1812433253>;
    using mt19937_64 = mersenne_twister_engine<uint_fast64_t,
                    64,312,156,31,0xb5026f5aa96619e9,
                    29,0x5555555555555555,
                    17,0x71d67fffeda60000,
                    37,0xfff7eee000000000,
                    43,6364136223846793005>; 
    
    using ranlux24_base = subtract_with_carry_engine <uint_fast32_t, 24, 10, 24>;
    using ranlux48_base = subtract_with_carry_engine <uint_fast64_t, 48, 5, 12>;
    
    using ranlux24 = discard_block_engine <ranlux24_base, 223, 23>;
    using ranlux48 = discard_block_engine <ranlux48_base, 389, 11>;
    
    using knuth_b = shuffle_order_engine <minstd_rand0,256>;
    
    using isaac32 = isaac_engine<uint32_t, 32, 0x9e3779b9>;
    using isaac64 = isaac_engine<uint64_t, 64, 0x9e3779b97f4a7c13>;
    
    using default_random_engine = ASSTL_RND_DEFAULT;
    
   
}


#endif /* RANDOM_HPP */

