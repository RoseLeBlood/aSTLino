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

#define IP4ANY             std::net::ip_address4(0x0000000000000000)
#define IP4LOOP            std::net::ip_address4(0x000000000100007F)
#define IP4BROADCAST       std::net::ip_address4(0x00000000FFFFFFFF)
        
#define IP6ANY             std::net::ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
#define IP6LOOP            std::net::ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },0);
#define IP4NONE            std::net::ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
 

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
            ip_address4() : ip_address_base(AddrFamily::Internet) { }
            ip_address4( int address) 
              : ip_address_base(AddrFamily::Internet) {
               m_address = (long)addr & 0x00000000FFFFFFFF;
            }
            ip_address4(unsigned short addr[4]) 
               : ip_address_base(AddrFamily::Internet)  {
               m_address = ((addr[3] << 24 | addr[2] <<16 | addr[1] << 8| addr[0]) & 0x0FFFFFFFF);
            }
            ip_address4(const ip_address4& v)
            	: ip_address_base(v.getFamily()) {
            	m_address = v.m_address;
            }	
            void getaddress(unsigned short b[4]) {
                b[0] = (unsigned short)(m_address);
                b[1] = (unsigned short)(m_address >> 8);
                b[2] = (unsigned short)(m_address >> 16);
                b[3] = (unsigned short)(m_address >> 24);
            }
            long get() { return m_address; }
            void set(long value) {
                if(!(value < 0 || value > 0x00000000FFFFFFFF))
                m_address = value;  
            }
            ip_address4& operator = (const ip_address4& v) {
                m_address = v.m_address; return *this; 
            }
            std::string to_string() {
                char buf[16]; //127.000.000.001(014)
                int len = sprintf(buf, "%d.%d.%d.%d",
                    (m_address >> 24) & 0xFF,
                    (m_address >> 16) & 0xFF,
                    (m_address >>  8) & 0xFF,
                    (m_address      ) & 0xFF);
            
                 return std::string(buf, len);
            }
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
            ip_address6() : ip_address_base(AddrFamily::InternetV6) { }
            ip_address6(unsigned short addr[16], long scopid = 0) 
            	:  ip_address_base(AddrFamily::InternetV6),  m_scopid(scopid) {
               
            	for (int i = 0; i < 8; i++) 
                    m_numbers[i] = (unsigned short)(addr[i * 2] * 256 + addr[i * 2 + 1]);
            	
            }
            ip_address6(const ip_address6& v) 
            	: ip_address_base(v.getFamily()), m_scopid(v.m_scopid) {
            	for(int i =0; i < 8; i++)
                  m_numbers[i] = v.m_numbers[i];            
            }
            ip_address6(const ip_address4& v) {
		m_numbers[0] = m_numbers[1] = m_numbers[2] = m_numbers[3] = m_numbers[4] = 0;  
            	m_numbers[5] = 0xFFFF;
            	m_numbers[6] = (unsigned short)(((v.get() & 0x0000FF00) >> 8) | ((v.get() & 0x000000FF) << 8));
            	m_numbers[7] = (unsigned short)(((v.get() & 0xFF000000) >> 24) | ((v.get() & 0x00FF0000) >> 8));
            	m_scopid = 0;  
            }
            
            void getaddress(unsigned short b[16]) {
            	for(int i=0, j =0; i < 8; i++){
                	b[j++] = (unsigned char)((m_numbers[i] >> 8) & 0xFF);
                	b[j++] = (unsigned char)((m_numbers[i]     ) & 0xFF);
            }
           
            long getscopid() { return m_scopid; }
            void setscopid(long id) { if(m_scopid != id) m_scopid = id; }
            
            
            ip_address6& operator = (const ip_address6& v) {
               for(int i =0; i < 8; i++)
                	m_numbers[i] = v.m_numbers[i];     
            	m_scopid = v.m_scopid;
            	return *this;
	    }
            
            unsigned short* get() { return m_numbers; }
           
            const ip_address4& to_ip4() {
		long address = ((((uint32_t)m_numbers[6] & 0x0000FF00u) >> 8) | (((uint32_t)m_numbers[6] & 0x000000FFu) << 8)) |
                    (((((uint32_t)m_numbers[7] & 0x0000FF00u) >> 8) | (((uint32_t)m_numbers[7] & 0x000000FFu) << 8)) << 16);
 
            	return ip_address4(address);
	    }
            
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

