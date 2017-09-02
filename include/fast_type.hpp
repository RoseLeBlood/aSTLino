/*
 * The MIT License
 *
 * Copyright 2017 annas.
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
 * File:   fast_type.hpp
 * Author: annas
 *
 * Created on 2. Mai 2017, 00:36
 */

#ifndef FAST_TYPE_HPP
#define FAST_TYPE_HPP

#include "common.hpp"

namespace std {
    class fbit {
    public:
        union {
            unsigned char bit : 1;
        };
        fbit() : bit(0) { }
        fbit(bool b) { bit = b ? 1 : 0; }
        fbit(const fbit& b) : bit(b) { }
 
        operator bool() { return bit == 1; }
        fbit& operator = (const fbit& other) {
            bit = other.bit;
        }
        bool operator == (const fbit& other) {
            return bit == other.bit;
        }
        bool operator != (const fbit& other) {
            return bit != other.bit;
        }
        
        void flip() { bit = (bit ==1) ? 0 : 1; }
    };
    
    
    
    template <size_t Bits, typename TBaseType>
    class fast_type {
    public:
        using self_type = fast_type<Bits, TBaseType>;
        using value_type = TBaseType;
        using bit_type = fbit;
        
        union {
            value_type Value;
            bit_type bits[Bits];
        };
        explicit fast_type(value_type v) : Value(v) {}
        fast_type(const fast_type& c) {
            Value = c.Value;
        }
        
        unsigned int count() { 
            unsigned int i;
            for(int j = 0; j < Bits; j++)
                i += bits[i].bit;
            return i;
        }
        unsigned int zeros() { 
            return Bits-count(); 
        }
        unsigned int set(size_t pos, bool p) {
            bits[pos].bit = p ? 1 : 0;
        } 
        size_t size() {
            return Bits;
        }
        
        value_type& operator [] (const size_t p) {
            return bits[p];
        }
        self_type& operator = (value_type& v) {
            Value = v; return *this;
        }
        self_type& operator = (self_type& other) {
            Value = other.Value; return *this;
        }
        bool operator == (self_type& other) {
            return Value == other.Value;
        }
        bool operator != (self_type& other) {
            return Value != other.Value;
        }
        bool operator <= (self_type& other) {
            return Value <= other.Value;
        }
        bool operator >= (self_type& other) {
            return Value >= other.Value;
        }
        bool operator < (self_type& other) {
            return Value < other.Value;
        }
        bool operator > (self_type& other) {
            return Value > other.Value;
        }
        
        self_type& operator += (self_type& other) {
            Value += other.Value; return *this;
        }
        self_type& operator -= (self_type& other) {
            Value -= other.Value; return *this;
        }
        self_type& operator *= (self_type& other) {
            Value *= other.Value; return *this;
        }
        self_type& operator &= (self_type& other) {
            Value &= other.Value; return *this;
        }
        self_type& operator |= (self_type& other) {
            Value |= other.Value; return *this;
        }
        self_type& operator ^= (self_type& other) {
            Value ^= other.Value; return *this;
        }
        self_type& operator <<= (self_type& other) {
            Value <<= other.Value; return *this;
        }
        self_type& operator >>= (self_type& other) {
            Value >>= other.Value; return *this;
        }
        self_type& operator /= (self_type& other) {
            Value /= other.Value; return *this;
        }
        self_type& operator += (value_type& v) {
            Value += v; return *this;
        }
        self_type& operator -= (value_type& v) {
            Value -= v; return *this;
        }
        self_type& operator *= (value_type& v) {
            Value *= v; return *this;
        }
        self_type& operator /= (value_type& v) {
            Value /= v; return *this;
        }
        self_type& operator <<= (value_type& v) {
            Value <<= v; return *this;
        }
        self_type& operator >>= (value_type& v) {
            Value >>= v; return *this;
        }
        self_type& operator - ( const self_type& rhs) {
            return self_type(*this) -= rhs;
        }
        self_type& operator + ( const self_type& rhs) {
            return self_type(*this) += rhs;
        }
        self_type& operator * ( const self_type& rhs) {
            return self_type(*this) *= rhs;
        }
        self_type& operator / ( const self_type& rhs) {
            return self_type(*this) /= rhs;
        }
        self_type& operator << ( const self_type& rhs) {
            return self_type(*this) <<= rhs;
        }
        self_type& operator >> ( const self_type& rhs) {
            return self_type(*this) >>= rhs;
        }
        self_type& operator | ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.Value |= rhs.Value;
            return result;
        }
        self_type& operator ^ ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.Value ^= rhs.Value;
            return result;
        }
        self_type& operator & ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.Value &= rhs.Value;
            return result;
        }
        self_type& operator ~ () {
            self_type result = self_type(*this);
            result.Value = ~result.Value;
            return result;
        }
        
        self_type& operator ++ () {
            Value++; return *this;
        }
        self_type& operator -- () {
            Value--; return *this;
        }
        self_type& operator ~ () {
            Value = ~Value; return *this;
        }
    };
    

    using fuint8_t = fast_type<8, uint8_t>;
    using fuint16_t = fast_type<16, uint16_t>;
    using fuint32_t = fast_type<32, uint32_t>;
    using fuint64_t = fast_type<64, uint64_t>;
    
    using fuint_least8_t = fast_type<8, fuint_least8_t>;
    using fuint_least16_t = fast_type<16, fuint_least16_t>;
    using fuint_least32_t = fast_type<32, fuint_least32_t>;
    using fuint_least64_t = fast_type<64, fuint_least64_t>;
    
    using fint8_t = fast_type<8,   int8_t>;
    using fint16_t = fast_type<16, int16_t>;
    using fint32_t = fast_type<32, int32_t>;
    using fint64_t = fast_type<64, int64_t>;
    
    using fint_least8_t = fast_type<8, fint_least8_t>;
    using fint_least16_t = fast_type<16, fint_least16_t>;
    using fint_least32_t = fast_type<32, fint_least32_t>;
    using fint_least64_t = fast_type<64, fint_least64_t>;
    
}


#endif /* FAST_TYPE_HPP */
