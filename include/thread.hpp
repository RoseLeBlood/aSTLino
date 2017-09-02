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
 * File:   thread.hpp
 * Author: annas
 *
 * Created on 14. November 2016, 21:47
 */

#ifndef _STD_THREAD_HPP_
#define _STD_THREAD_HPP_

#include "common.hpp"
#include "auto_ptr.hpp"

typedef void  (*thread_func) ( void* arg);

#include <pthread.h>
namespace std
{
    typedef pthread_t native_thread_handle;
    class thread 
    {
    public:
	thread();
	thread(thread_func lpExternalRoutine);
	~thread();

	int start(void* arg = NULL);
        int exit();
        int join();
        
        uint64_t  get_pid();
        uint32_t get_retCode() { return m_errorCode; }
	void attach(thread_func lpThreadStartRoutine );
	void detach(void);
        
        const native_thread_handle handle() { return m_ThreadCtx; }
        
        static void sleep(long ms);
    protected:
	static void* EntryPoint( void* pArg);

	virtual int Run( void*  arg  );
    private:
	native_thread_handle m_ThreadCtx;
        void* m_pUserdata;
        uint32_t m_errorCode;
	thread_func	m_pThreadStartRoutine;
    };
}

#endif /* THREAD_HPP */

