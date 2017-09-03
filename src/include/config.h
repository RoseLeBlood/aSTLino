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
 * File:   config.h
 * Author: annas
 *
 * Created on 11. Dezember 2016, 00:48
 */

#ifndef ASSTL_VERSION
#define ASSTL_VERSION 0x00242 // v. 0.22.8
#endif

#ifndef ASSTL_VERSION_STRING
#define ASSTL_VERSION_STRING std::string("0.24.2")
#endif
#ifndef USER_SYSTEM_IMP_
/*
 See PLATFORM.cpp - when defined USER_SYSTEM_IMP_you must own impl in 
 *  PLATFORM.cpp 
 */
#define USER_SYSTEM_IMP_ 1 
#endif


#ifndef ASSTL_SYSTEM_NAME
    #ifdef USER_SYSTEM_IMP_ 
        #define ASSTL_SYSTEM_NAME "Arduino"
	
    #else
        #if defined(__linux__)
            #define ASSTL_SYSTEM_NAME "linux"
        #elif defined(BSD)
            #define ASSTL_SYSTEM_NAME "bsd"
        #elif defined(__CYGWIN__) && !defined(_WIN32)
            #define ASSTL_SYSTEM_NAME "cygwin"
        #elif defined(_WIN64)
            #if defined(__MINGW64__)
                #define ASSTL_SYSTEM_NAME "mingw64"
            #else
                #define ASSTL_SYSTEM_NAME "win64"
            #endif
        #elif defined(_WIN32)
            #if defined(__MINGW32__)
                #define ASSTL_SYSTEM_NAME "mingw32"
            #else
                #define ASSTL_SYSTEM_NAME "win32"
            #endif
        #endif
    #endif // USER_SYSTEM_IMP_
#endif // ASSTL_SYSTEM_NAME

#ifndef ASSTL_LIB_NAME // see asstl.cpp
#define ASSTL_LIB_NAME ((ASSTL_VERSION_STRING) << "-" << ASSTL_SYSTEM_NAME)
#endif

#ifndef ASSTL_RND_DEFAULT
#define ASSTL_RND_STD  std::minstd_rand
#define ASSTL_RND_STD0 std::minstd_rand0

#define ASSTL_RND_MT19937 std::mt19937
#define ASSTL_RND_MT19937_64 std::mt19937_64

#define ASSTL_RND_DEFAULT ASSTL_RND_STD
#endif

#ifndef ASSTL_LOCK_DEFAULT 
#define ASSTL_LOCK_ARDUINO std::alock
//#define ASSTL_LOCK_SPINLOCK std::spinlock
#define ASSTL_LOCK_DEFAULT ASSTL_LOCK_ARDUINO
#endif
#ifndef ASSTL_HASH_DEFAULT
#define ASSTL_HASH_ADLER32 std::adl32_t
#define ASSTL_HASH_BERNSTEIN std::brnst_t
#define ASSTL_HASH_FLETCHER16 std::flt16_t
#define ASSTL_HASH_FLETCHER16 std::flt32_t
#define ASSTL_HASH_CRC32K std::crc32_k; //0x741B8CD7
#define ASSTL_HASH_CRC32Q std::crc32_q; //0x814141AB
#define ASSTL_HASH_CRC32P std::crc32_t; //0x04c11db7
#define ASSTL_HASH_FNV1A std::fnv1a_t
#define ASSTL_HASH_WEINBERG std::wberg_t

#define ASSTL_HASH_DEFAULT ASSTL_HASH_ADLER32
#endif

#ifndef ASSTL_USE_SSE
//#define ASSTL_USE_SSE
#endif

#ifndef ASSTL_USE_OPENMP
//#define ASSTL_USE_OPENMP
#endif
