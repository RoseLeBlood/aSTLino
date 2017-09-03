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
 * File:   physicaladdress.cpp
 * Author: annas
 * 
 * Created on 9. April 2017, 22:01
 */

#include "include/network/physicaladdress.hpp"
#include "include/common.hpp"

namespace std {
    namespace net {
   
        physicaladdress::physicaladdress(unsigned char *addr, int elements) {
            m_iElements = elements;
            m_cAddress = std::Sys::mAllocE<unsigned char>(m_iElements);
            std::Sys::MemCpy(this->m_cAddress, addr, m_iElements);
        }
        physicaladdress::physicaladdress(const physicaladdress& orig) {
            m_iElements = orig.m_iElements;
            m_cAddress = std::Sys::mAllocE<unsigned char>(m_iElements);
            std::Sys::MemCpy(this->m_cAddress, orig.m_cAddress, m_iElements);
        }

        physicaladdress::~physicaladdress() {
            std::Sys::mFree(m_cAddress);
        }
        
        
    }
}
