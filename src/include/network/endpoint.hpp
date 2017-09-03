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
 * File:   endpoint.hpp
 * Author: annas
 *
 * Created on 26. Dezember 2016, 21:59
 */



#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include "address.hpp"
#include "../property.hpp"

namespace std {
    namespace net {
        template <class TIPAddr>
        class end_point {
        public:
            using ip_type = TIPAddr;
            using self_type = end_point<ip_type>;
            
            static constexpr uint32_t MinPort = 0;
            static constexpr uint32_t MaxPort = 0x0000FFFF;
            
            end_point() {
                m_ipAddr = ip_type::Any;
                m_port = MinPort;
            }
            end_point(ip_type addr, uint32_t port) {
                m_ipAddr = addr;
                m_port = port;
            }
            AddrFamily getFamely() {
                return m_ipAddr.getFamely(); 
            }
            ip_type get_addr() { return m_ipAddr; }
            uint32_t get_port() { return m_port; }
            
            void set_addr(ip_type addr) { m_ipAddr = addr; }
            void set_port(uint32_t port) { m_port = port; }
        private:
            ip_type m_ipAddr;
            uint32_t m_port;
        };
        class end_point4 : public end_point<ip_address4> {
        public:
            end_point4() : end_point() { }
            end_point4(ip_address4 addr, uint32_t port) 
                : end_point(addr, port) { }
        };
        class end_point6 : public end_point<ip_address6> {
        public:
            end_point4() : end_point() { }
            end_point4(ip_address6 addr, uint32_t port) 
                : end_point(addr, port) { }
        };
    }
}


#endif /* ENDPOINT_HPP */

