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
 * File:   property.hpp
 * Author: annas
 *
 * Created on 9. Mai 2017, 05:37
 */

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "common.hpp"
#include "auto_ptr.hpp"

namespace std {
    template <typename T, class TBase> 
    class property {
    public:
        using setter_type = void (TBase::*)(const T);
        using getter_type = T (TBase::*)();
        
        property(auto_ptr<TBase> base, getter_type gtyp, setter_type styp ) {
            m_aupClass = base;
            m_clGetter = gtyp;
            m_cSetter = styp;
        }
        operator T() const {
            assert(m_clGetter != 0);
            assert(m_aupClass.get() != 0);
            return (m_aupClass->*m_clGetter());
        }
        const auto_ptr<TBase> operator = (const T& value) {
            (m_aupClass->*m_cSetter(value));
            return m_aupClass;
        }
        const TBase& operator = (const property<T,TBase>& other) {
            m_aupClass = other.m_aupClass;
            m_clGetter = other.m_cSetter;
            m_cSetter = other.m_cSetter;
        }
    private:
        auto_ptr<TBase> m_aupClass;
        getter_type m_clGetter;
        setter_type m_cSetter;
    };
    
    template <class TBase> 
    class prop8_t : public property<int8_t, TBase> {
    public:
        prop8_t(auto_ptr<TBase> base, getter_type gtyp, setter_type styp ) 
            : property<int8_t, TBase>(base, gtyp, styp) { }
    };
    template <class TBase> 
    class prop16_t : public property<int16_t, TBase> {
    public:
        prop16_t(auto_ptr<TBase> base, getter_type gtyp, setter_type styp ) 
            : property<int16_t, TBase>(base, gtyp, styp) { }
    };
   
    
}


#ifndef prop_t
#define prop_t(base, type, name, get, set) \
         property<(type), (base)> (name){auto_ptr<base>((this)), (get), (set)}

#define prop8_t(base, name, get, set) prop_t(base, int8_t, (name), (get), (set))
#define prop16_t(base, name, get, set) prop_t(base, int16_t, (name), (get), (set))
#define prop32_t(base, name, get, set) prop_t(base, int32_t, (name), (get), (set))
#define prop64_t(base, name, get, set) prop_t(base, int64_t, (name), (get), (set))

#define propu8_t(base, name, get, set) prop_t(base, uint8_t, (name), (get), (set))
#define propu16_t(base, name, get, set) prop_t(base, uint16_t, (name), (get), (set))
#define propu32_t(base, name, get, set) prop_t(base, uint32_t, (name), (get), (set))
#define propu64_t(base, name, get, set) prop_t(base, uint64_t, (name), (get), (set))

#define propl_t(base, name, get, set) prop_t(base, long, (name), (get), (set))
#define propf_t(base, name, get, set) prop_t(base, float, (name), (get), (set))
#define propd_t(base, name, get, set) prop_t(base, double, (name), (get), (set))
#define propc_t(base, name, get, set) prop_t(base, char, (name), (get), (set))

#define propul_t(base, name, get, set) prop_t(base,unsigned long, (name), (get), (set))
#define propf_t(base, name, get, set) prop_t(base, float, (name), (get), (set))
#define propd_t(base, name, get, set) prop_t(base, double, (name), (get), (set))
#define propuc_t(base, name, get, set) prop_t(base,unsigned char, (name), (get), (set))

#define propcp_t(base, name, get, set) prop_t(base,const char*, (name), (get), (set))
#define propstr_t(base, name, get, set) prop_t(base, std::string, (name), (get), (set))


#endif
#endif /* PROPERTY_HPP */

