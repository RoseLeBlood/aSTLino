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
 * File:   singleton.hpp
 * Author: annas
 *
 * Created on 9. November 2016, 00:21
 */

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "auto_ptr.hpp"

namespace std
{
    template < typename T > 
    class singleton
    {
    public:
        using value_type = T;
        
        static value_type& get()
        {
            if( m_ptr.get() == 0 )
            {
                m_ptr.reset( new value_type() );
            }
            return *m_ptr;
        } 
    public:
        singleton() {}
        
      
    private:
        singleton(singleton const&)       = delete;
        void operator=(singleton const&)  = delete;

    private:
        static std::auto_ptr<T> m_ptr;   
    };
    template < typename T > 
    std::auto_ptr<T> singleton<T>::m_ptr = std::auto_ptr<T>(0);
}


#endif /* SINGLETON_HPP */

