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
 * File:   stream.hpp
 * Author: annas
 *
 * Created on 22. November 2016, 00:12
 */

#ifndef STREAM_HPP
#define STREAM_HPP

#include "common.hpp"

namespace std
{
    typedef enum class SeekOrigin
    {
        Beginn = 0,
        End = 2,
        Current = 1,
    }seek_t;
    


    class stream
    {
    public:
	stream() { }
	stream(bool canread, bool canwrite, bool canseek) 
		: m_canRead(canread), m_canWrite(canwrite), m_canSeek(canseek) { }
        stream(const stream& st) 
            :  m_canRead(st.m_canRead), m_canWrite(st.m_canWrite), m_canSeek(st.m_canSeek) { }
		
	virtual ~stream() { }

	virtual size_t seek(size_t off, seek_t org) { return 0; }
	
	virtual bool canRead() { return m_canRead; }
	virtual bool canSeek() { return m_canSeek; }
	virtual bool canWrite() { return m_canWrite; }
	
	virtual void clear() { }
	
	virtual void write(char c)  { }
	virtual char read() { return ' '; }
	
	virtual size_t read(void *data, size_t offset, size_t size) { return 0; }
	virtual size_t write(const void *data, size_t offset, size_t size) { return 0; }
        virtual long position() { return 0; }
        virtual long size() { return 0; }
        virtual bool iseof() { return false; }
        virtual void flush() { }
        
        
    protected:
	bool		m_canRead;
	bool		m_canWrite;
	bool 		m_canSeek;
    };
}

#endif /* STREAM_HPP */

