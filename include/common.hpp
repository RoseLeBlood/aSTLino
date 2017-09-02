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
 * File:   common.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:14
 */

#ifndef _STD_COMMON_H_
#define _STD_COMMON_H_



#include "config.h"
#include "unknown.hpp"

#undef __STRICT_ANSI__ 
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>		
#include <limits.h>
#include <float.h>


#ifndef override
#define override virtual 
#endif
namespace std 
{ 
        class Sys 
        {
        public:
            static void MemCpy(void* to, const void* from, size_t bytes);
            static void MemMove(void* to, const void* from, size_t bytes);
            static void MemSet(void* buf, unsigned char value, size_t bytes);
                
            static void wMemCpy(void* to, const void* from, size_t bytes);
            static void wMemMove(void* to, const void* from, size_t bytes);
            static void wMemSet(void* buf, unsigned char value, size_t bytes);
                
            static int vsnPrintf(char *buffer, size_t count, const char *format, va_list argptr);
            static int fPrintf(void* file, const char* str);
                
            static void* fOpen(const char* file, const char* fmt);
            static void fClose(void* file);
            static int fTell(void* file);
            static int fPutc(int c, void* file);
            static int fPuts(const char* str, void* file);
            static int fGetc(void* file);
            static int fSeek(void* file, int off, int org);
            static int fRead(void* data, const int count, const int size, void* file);
            static int fWrite(void* data, const int count, const int size, void* file);
            static int fFlush(void* file);
            static int fEOF(void* file);
            static int fError(void* file); 
            static bool fIsFile(const char* file);
                
            static void* mAlloc(size_t size);
            static void* mReAlloc(void* old, size_t newSize);
            static void  mFree(void* mem);
              
            template <typename T>
            static T* mAllocE(int elements) {
                return (T*)Sys::mAlloc(sizeof(T) * elements);
            }    
           /* typedef struct mutex_struct {} mutex_type ;
            enum class mutex_init_t {
                Normal,
                Recursive,
                ErrorCheak,
                Default = mutex_init_t::Normal,
            }; 
            static int mutexInit(mutex_type* mutex, mutex_init_t type = mutex_init_t::Normal,
                                 bool shared = false, bool robust = false);
            static int mutexDestroy(mutex_type* mutex);
            static int mutexLock(mutex_type* mutex);
            static int mutexUnLock(mutex_type* mutex);
            static int mutexTryLock(mutex_type* mutex);
                
                
                typedef struct spinlock_struct {} spinlk_type;
                
            static int spinlockInit(spinlk_type* mutex, const void* attr);
            static int spinlockDestroy(spinlk_type* mutex);
            static int spinlockLock(spinlk_type* mutex);
            static int spinlockUnLock(spinlk_type* mutex);
            static int spinlockTryLock(spinlk_type* mutex); 
            
            static uint64_t pTotalMem();*/
        }; 
}

namespace std
{
	enum class e_noinitialize
	{
	        noinitialize
	};
}

#endif


