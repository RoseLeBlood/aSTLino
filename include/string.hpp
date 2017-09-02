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
 * File:   string.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 01:11
 */

#ifndef _STD_STRING_H_

#define _STD_STRING_H_
#define _STD_WSTRING_H_

#include "basic_string.hpp"
#include "hash.hpp"
#include "vector.hpp"
#include "common.hpp"

namespace std
{
	using string = basic_string<char>;
	
        
        enum class flags_t
	{
            boolalpha =	0x0001,
            showbase  =	0x0002,
            showpoint =	0x0004,
            showpos =	0x0008,
            skipws =	0x0010,
            unitbuf =   0x0020, 
            uppercase =	0x0040, 
            dec =	0x0080,
            hex =	0x0100,
            oct =	0x0200,
            bin =	0x0400,
            internal =	0x0800, 
            hexbase = 	0x0100 | 0x0002
	};
        inline bool operator & (flags_t a, flags_t b){
            return ((int)a) & ((int)b);
        }
	namespace internal {
            template<typename E, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
            inline basic_string<E, TAllocator, TStorage> __flagstostring(std::flags_t f = std::flags_t::dec ) {
                if (f & flags_t::dec)
                    return basic_string<E, TAllocator, TStorage>("d");
		else if (f & flags_t::hex && f & flags_t::showbase)
                    return basic_string<E, TAllocator, TStorage>("0x%X");
		else if (f & flags_t::hex)
                    return basic_string<E, TAllocator, TStorage>("%X");
		else if (f & flags_t::oct)
                    {}//itoa(buf, 8, i);
		else if (f & flags_t::bin)
                    return basic_string<E, TAllocator, TStorage>("%b");
		return basic_string<E, TAllocator, TStorage>("%d");
            }
            template<class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<char, TAllocator> >
            inline basic_string<char, TAllocator, TStorage> __flagstostring(std::flags_t f = std::flags_t::dec ) {
                return __flagstostring<char, TAllocator, TStorage>(f); 
            }
        }
        
	template<typename E, class TAllocator, typename TStorage>
	struct hash<basic_string<E, TAllocator, TStorage>>
	{
	    hash_value_t operator()(const basic_string<E, TAllocator, TStorage>& x) const 
	    {
                return hasher<default_hasher>::get().hash(x.c_str() ,x.length());
	    }
	};
	
	

        template<typename E, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline size_t frmstring(
            basic_string<E, TAllocator, TStorage>& dest, const char* format, va_list arg)
        {
            size_t length;
            va_list apStrLen;
            va_copy(apStrLen, arg);
            length = Sys::vsnPrintf(NULL, 0, format, apStrLen);
            va_end(apStrLen);
                
                
            if (length > 0) {
                dest.resize(length);
                Sys::vsnPrintf(dest.data(), dest.length(), format, arg);
            }
               
            return length;
        }
	template<typename E, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
	inline basic_string<E, TAllocator, TStorage> frmstring( const char* format, ...)
        {
            va_list ap;
            va_start(ap, format);
            basic_string<E, TAllocator, TStorage> dest;
            frmstring<E, TAllocator, TStorage>(dest, format, ap);
            va_end(ap);
            return dest;
        }
        template<class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<char, TAllocator> >
	inline basic_string<char> frmstring( const char* format, ...)
        {
            va_list ap;
            va_start(ap, format);
            basic_string<char, TAllocator, TStorage> dest;
            frmstring<char, TAllocator, TStorage>(dest, format, ap);
            va_end(ap);
            return dest;
        }
        
       
        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> to_string(const int32_t v, flags_t f = flags_t::dec  ) { 
            std::basic_string<E, TAllocator, TStorage> fmt = 
                    internal::__flagstostring<E, TAllocator, TStorage >(f);
            return std::frmstring<E, TAllocator, TStorage>(fmt.c_str(), v); }
        
        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> to_string(const int64_t v, flags_t f = flags_t::dec  ) { 
            std::basic_string<E, TAllocator, TStorage> fmt = 
                    internal::__flagstostring<E, TAllocator, TStorage >(f);
            return std::frmstring<E, TAllocator, TStorage>(fmt.c_str(), v); }
        
        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> to_string(const uint32_t v, flags_t f = flags_t::dec  ) { 
            std::basic_string<E, TAllocator, TStorage> fmt = 
                    internal::__flagstostring<E, TAllocator, TStorage >(f);
            return std::frmstring<E, TAllocator, TStorage>(fmt.c_str(), v); }
        
        template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
        inline std::basic_string<E, TAllocator, TStorage> to_string(const uint64_t v, flags_t f = flags_t::dec  ) { 
            std::basic_string<E, TAllocator, TStorage> fmt = 
                    internal::__flagstostring<E, TAllocator, TStorage >(f);
            return std::frmstring<E, TAllocator, TStorage>(fmt.c_str(), v); }
        
        template<typename E = char, class TAllocator, typename TStorage>
        inline std::basic_string<E, TAllocator, TStorage> to_string(const float v, flags_t f = flags_t::dec  ) {  
            return std::frmstring("%f", v); }
        
        template<typename E = char, class TAllocator, typename TStorage>
        inline std::basic_string<E, TAllocator, TStorage> to_string(const double v, flags_t f = flags_t::dec  ) {  
            return std::frmstring("%f", v); }
        
        template<typename E = char, class TAllocator, typename TStorage>
        inline std::basic_string<E, TAllocator, TStorage> to_string(const bool v, flags_t f = flags_t::dec  ) {   
            return std::frmstring("%s", (v ? "true" : "false") ); }
        
        template<typename E = char, class TAllocator, typename TStorage>
        inline std::basic_string<E, TAllocator, TStorage> to_string(const void* v, flags_t f = flags_t::dec  ) {   
            return std::frmstring("%p", v ); }
}

#endif 


