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
 * File:   enums.hpp
 * Author: annas
 *
 * Created on 11. Mai 2017, 16:19
 */

#ifndef ENUMS_HPP
#define ENUMS_HPP

namespace std {
    namespace net {
        enum class ProcType {
            Unknown = -1,
            IP = 0,
            ICMP = 1,
            IGMP = 2,
            IPv4 = 4,
            TCP = 6,
            UDP = 17,
            IDP = 22,
            IPv6 = 41,
            IPv6RoutingHeader = 43,
            IPv6FragmentHeader = 44,
            IcmpV6 = 58,
            IPv6NoNextHeader = 59,
            IPv6DestinationOptions = 60,
            
            User = 255
        };
        enum class AddrFamily {
            Unknown =-1,
            null = 0,
            Unix = 1,
            Internet = 2,
            InternetV6 = 23,
            ArpaNet = 3,
            IrDa = 4,
        };
        enum class SocketTyp {
            Stream,
            Dgram,
            Raw,
            Rdm,
            Seqpacket,
            Other
        };
        enum class SocketInformationOptions {
            NonBlocking = 0x1,
            Conected = 0x2,
            Listing = 0x4,
            UseOnlyOverlappedIO = 0x8
        };
    }
}

#endif /* ENUMS_HPP */

