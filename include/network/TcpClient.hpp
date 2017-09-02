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
 * File:   TcpClient.hpp
 * Author: annas
 *
 * Created on 11. Mai 2017, 18:05
 */

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include "socket.hpp"

namespace std {
    namespace net {
        
        template <typename IpAddr>
        class TcpClient {
        public:
            TcpClient() {
                
            }
            TcpClient(IpAddr addr, int port) {
                
            }
            TcpClient(end_point<IpAddr> ep) {
                
            }
            TcpClient<IpAddr> AcceptTcpClient() {
                
            }
            socket<IpAddr> Accept() {
                
            }
            static TcpClient<IpAddr> Create(int port) {
                
            }
            bool pending() {
                
            }
            void start(int backlog) {
                
            }
            void stop() {
                
            }
        };
        class TcpClient4 : public TcpClient<ip_address4> {
        public:
            TcpClient4() : TcpClient<ip_address4>() {}
            TcpClient4(ip_address4 addr, int port) : TcpClient<ip_address4>(addr, port) {}
            TcpClient4(end_point<ip_address4> ep) : TcpClient<ip_address4>(ep) {}
        };
        class TcpClient6 : public TcpClient<ip_address6> {
        public:
            TcpClient6() : TcpClient<ip_address6>() {}
            TcpClient6(ip_address6 addr, int port) : TcpClient<ip_address6>(addr, port) {}
            TcpClient6(end_point<ip_address6> ep) : TcpClient<ip_address6>(ep) {}
        };
    }
}

#endif /* TCPCLIENT_HPP */

