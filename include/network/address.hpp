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
 * File:   address.hpp
 * Author: annas
 *
 * Created on 26. Dezember 2016, 22:06
 */

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "enums.hpp"
#include "../string.hpp"

namespace std {
    namespace net {
        
        class ip_address_base {
        public:
            ip_address_base() : m_addr(AddrFamily::Unknown) {}
            ip_address_base(AddrFamily addr) : m_addr(addr) { }
            
            virtual AddrFamily getFamily() {
                return m_addr; 
            }
            
        protected:
            AddrFamily m_addr;
        };
        class ip_address4 : public ip_address_base {
        public:
            static const ip_address4 Any;// = ip_address4(0x0000000000000000);
            static const ip_address4 Loop;// = ip_address4(0x000000000100007F);
            static const ip_address4 BroadCast;// = ip_address4(0x00000000FFFFFFFF);

            
            ip_address4() : ip_address_base(AddrFamily::Internet) { }
            ip_address4( int address);
            ip_address4(const ip_address4& v);
            explicit ip_address4(unsigned short addr[4]);
            
            void getaddress(unsigned short b[4]);
            long get();
            void set(long value);
            
            static ip_address4 parse(std::string ip); 
            
            ip_address4& operator = (const ip_address4& v);
            
            std::string to_string();
        private:
            unsigned int m_address;
        };
        inline bool operator == (const ip_address4& a, const ip_address4& b ) {
            return a.get() == b.get();
        }
        inline bool operator != (const ip_address4& a, const ip_address4& b ) {
            return a.get() != b.get();
        }
        
        
        class ip_address6 : public ip_address_base  {
        public:
            static const ip_address6 Any      ;//= ip_address6(unsigned char[]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
            static const ip_address6 Loopback ;//= ip_address6(unsigned char[]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },0);
            static const ip_address6 None     ;//= ip_address6(unsigned char[]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
 
            ip_address6() : ip_address_base(AddrFamily::InternetV6) { }
            ip_address6(unsigned short addr[16], long scopid);
            ip_address6(unsigned short addr[16]);
            ip_address6(const ip_address6& v);
            ip_address6(const ip_address4& v);
            
            void getaddress(unsigned short b[16]);
           
            long getscopid();
            void setscopid(long id);
            
            static ip_address6 parse(std::string ip) { return ip_address6(); } 
            
            ip_address6& operator = (const ip_address6& v);
            
            unsigned short* get() { return m_numbers; }
           
            const ip_address4& to_ip4();
            
            bool is_multicast() { return ((m_numbers[0] & 0xFF00 ) == 0xFF00 ); }
            bool is_linklocal() { return ((m_numbers[0] & 0xFFC0 ) == 0xFE80 ); }
            bool is_sitelocal() { return ((m_numbers[0] & 0xFFC0 ) == 0xFEC0 ); }
            bool is_teredo() { return (m_numbers[0] == 0x2001 ) && ( m_numbers[1] == 0 ); }
            bool is_ipv4mapped() {
                for (int i = 0; i < 5; i++) {
                    if (m_numbers[i] != 0) {
                        return false;
                    }
                }
                return (m_numbers[5] == 0xFFFF);
            }
            
        private:
            long m_scopid;
            unsigned short  m_numbers[8];
        };
        inline bool operator == (const ip_address6& a, const ip_address6& b ) {
            for(int i =0; i < 8; i++)
                if (a.get()[i] != b.get()[i]) return false;
            return a.getscopid() == b.getscopid();               
        }
        inline bool operator != (const ip_address6& a, const ip_address6& b ) {
            return !(a == b);
        }
        
        
    }
}


#endif /* ADDRESS_HPP */

