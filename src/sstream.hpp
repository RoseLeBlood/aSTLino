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
 * File:   sstream.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 22:16
 */

#ifndef _STD_STRINGSTREAM_H_
#define _STD_STRINGSTREAM_H_

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"
#include <string.h>

namespace std 
{
    template< typename E, typename TAlloc = std::allocator > 
    class basic_stringstream
    {
        using value_type = E;
        using buffer_type =  std::vector<value_type, TAlloc>;
        using size_type =  typename buffer_type::size_type;
        using string_type = basic_string<value_type, TAlloc>;
        
        explicit basic_stringstream(const value_type* inp) 
        { 
        	init(inp); 
        }
        explicit basic_stringstream(const string_type& inp) 
        { 
        	init(inp.c_str()); 
        }

        basic_stringstream() 
        {
        
        }
 
        bool good() const 
        { 
        	return buffer.size() ? cursor != buffer.end() : false; 
        }
        bool eof() const 
        { 
        	return !good(); 
        }
        operator bool() const 
        { 
        	return good(); 
        }
        
        void reset(const value_type* inp) 
        {
            init(inp);
        }
        string_type str()
        {
        	string_type	strr = string_type();
        	
        	while(next())
        	{
        		strr.append(current);
        	}
        	return strr;
        }
        //------------------------------------------------------
        //Output operators
        basic_stringstream& operator>>(int& x) 
        {
	        if( next() ) 
	            x = atoi((const char*)current.c_str());
	        return *this;
        }
        basic_stringstream& operator>>(long& x) 
        {
            if( next() ) 
                x = atol((const char*)current.c_str());
            return *this;
        }
        basic_stringstream& operator>>(float& x) 
        {
            if( next() ) 
                x = atof((const char*)current.c_str());
            return *this;
        }
        basic_stringstream& operator>>(std::string& x) 
        {
            if( next() ) 
                x = current;
            return *this;
        }  
        basic_stringstream& operator>>(const char& x) 
        {
            if( next() ) 
                x = current.c_str();
            return *this;
        }        
    private:
        void init(const value_type* inp) 
        {
            if( !inp || !strlen(inp) ) 
            {
                cursor = buffer.end();
                return;
            }
            const size_type len = strlen(inp);
            buffer.resize(len);
            memmove(buffer.begin(), inp, len);
            cursor = buffer.begin();
            current.clear();
            ltrim();
        }
        
        bool is_whitespace(const value_type& ch) const 
        {
            return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
        }
        
        void ltrim() 
        {
            while(is_whitespace(*cursor)) 
                ++cursor;
        }
        
        bool next() 
        {
            if(!buffer.size())
                return false;
            current.clear();
            for(; cursor!=buffer.end(); ++cursor) 
            {
                if(!is_whitespace(*cursor)) 
                {
                    current.append(*cursor);   
                } else 
                {
                    ltrim();
                    break;
                }
            }
            return current.length();
        }
        
        string_type 						 current;
        buffer_type 						 buffer;
        typename buffer_type::const_iterator cursor;
    };    
    typedef basic_stringstream<char> stringstream;
}


#endif


