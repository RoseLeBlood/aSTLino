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

#include "common.hpp"


#include <Arduino.h>


namespace std {
     
                void Sys::MemCpy(void* to, const void* from, size_t bytes) {
                  memcpy(to, from, bytes);
                }
                void Sys::MemMove(void* to, const void* from, size_t bytes) {
                  memmove(to, from, bytes);
                }
                void Sys::MemSet(void* buf, unsigned char value, size_t bytes) {
                  memset(buf, value, bytes);
                }
                
                void Sys::wMemCpy(void* to, const void* from, size_t bytes) {
                       
                }
                void Sys::wMemMove(void* to, const void* from, size_t bytes) {
                       
                }
                void Sys::wMemSet(void* buf, unsigned char value, size_t bytes) {
                        
                }
                int Sys::vsnPrintf(char *buffer, size_t count, const char *format, va_list ap) {
#ifdef __AVR__
                  return vsnprintf_P(buffer, count, (const char *)format, ap); 
#else
                  return vsnprintf(buffer, count, (const char *)format, ap);
#endif
                }
                
                void* Sys::fOpen(const char* file, const char* fmt) {                  
                  if(strcmp(file, "stdout")==0) Serial.begin(9600);
                    return malloc(10);
                }
                void  Sys::fClose(void* file) {
                    free(file);
                }
                int Sys::fTell(void* file) {
                    return Serial.peek();
                }
                int Sys::fPutc(int c, void* file) {
                    Serial.print((char)c);
                }
                int Sys::fPuts(const char* str, void* file) {
                    Serial.print(str);
                }
                int Sys::fGetc(void* file) {
                   return Serial.read();
                }
                int Sys::fPrintf(void* file, const char* str) {
		              Serial.print(str);
                  return strlen(str);
                }
                int Sys::fSeek(void* file, int off, int org) {
                    return 0;
                }
                int Sys::fRead(void* data, const int count, const int size, void* file) {
                    
                    /*for(int i =0; i<size; i++)
                       data[i] = Serial.read();*/
                    return 0;
                }
                
                int Sys::fWrite(void* data, const int count, const int size, void* file) {
                    char* g = (char*)data;
                    
                    for(int i =0; i<size; i++)
                      Serial.print( (char)(g[i]) );
                }
                int Sys::fFlush(void* file) {
                    Serial.flush();
                    return 0;
                }
                int Sys::fEOF(void* file) {
                    return 0;
                }
                int Sys::fError(void* file) {
                    return 0;
                }
                bool Sys::fIsFile(const char* file) {
                    return false;
                }  
                void* Sys::mAlloc(size_t size) {
                    return malloc(size);
                }
                void* Sys::mReAlloc(void* old, size_t newSize) {
                    if(sizeof(old) < newSize) 
                    {
                        void* n = malloc(newSize);
                        memmove(n, old, newSize); return n;
                    }
                    return old;
                }
                void  Sys::mFree(void* mem) {
                    free(mem);
                }
                /*int Sys::mutexInit(mutex_type* mutex, mutex_init_t type,
                        bool shared, bool robust) {
                    return 0;
                }
                    
                int Sys::mutexDestroy(mutex_type* mutex) {
                    return 0;
                }
                int Sys::mutexLock(mutex_type* mutex) {
                    return -1;
                }
                int Sys::mutexUnLock(mutex_type* mutex) {
                    return -1;
                }
                int Sys::mutexTryLock(mutex_type* mutex) {
                    return -1;
                }
                int Sys::spinlockInit(spinlk_type* spin, const void* attr) {
                   return -1;
                }
                int spinlockDestroy(spinlk_type* spin) {
                   return -1;
                }
                int spinlockLock(spinlk_type* spin) {
                   return -1;
                }
                int Sys::spinlockUnLock(spinlk_type* spin) {
                   return -1;
                }
                int Sys::spinlockTryLock(spinlk_type* spin) {
                   return -1;
                }
                uint64_t Sys::pTotalMem() {
                   return 0;
                }*/
};
        

