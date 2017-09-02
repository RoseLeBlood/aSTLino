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

#include "include/network/address.hpp"
#include "include/common.hpp"

namespace std {
    namespace net {
        const ip_address4 ip_address4::Any = ip_address4(0x0000000000000000);
        const ip_address4 ip_address4::Loop = ip_address4(0x000000000100007F);
        const ip_address4 ip_address4::BroadCast = ip_address4(0x00000000FFFFFFFF);
        
        const ip_address6 ip_address6::Any      = ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
        const ip_address6 ip_address6::Loopback = ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },0);
        const ip_address6 ip_address6::None     = ip_address6( new short[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },0);
 
        ip_address4::ip_address4( int addr) 
            : ip_address_base(AddrFamily::Internet) {
            m_address = (long)addr & 0x00000000FFFFFFFF;
        }
        ip_address4::ip_address4(unsigned short addr[])
            : ip_address_base(AddrFamily::Internet)  {
            m_address = ((addr[3] << 24 | addr[2] <<16 | addr[1] << 8| addr[0]) & 0x0FFFFFFFF);
        }
        ip_address4::ip_address4(const ip_address4& v)
            : ip_address_base(v.getFamily()) {
            m_address = v.m_address;
        }
        void ip_address4::getaddress(unsigned short b[4]) {
            b[0] = (unsigned short)(m_address);
            b[1] = (unsigned short)(m_address >> 8);
            b[2] = (unsigned short)(m_address >> 16);
            b[3] = (unsigned short)(m_address >> 24);
        }
        
        void ip_address4::set(long value) {
            if(!(value < 0 || value > 0x00000000FFFFFFFF))
                m_address = value; 
        }
        long ip_address4::get() {
            return m_address; 
        }
        ip_address4& ip_address4::operator = (const ip_address4& v) { 
            m_address = v.m_address; return *this; 
        }
        std::string ip_address4::to_string() {
            std::string dest ;
            dest = std::frmstring("%d.%d.%d.%d",
                    (m_address >> 24) & 0xFF,
                    (m_address >> 16) & 0xFF,
                    (m_address >>  8) & 0xFF,
                    (m_address      ) & 0xFF);
            
            return dest;
        }

        ip_address4 ip_address4::parse(std::string _ip) {
            const char* s_ip = _ip.c_str();
            unsigned int ip = 0;
            unsigned char * c_ip = (unsigned char *)&ip;
            sscanf(s_ip, "%hhu.%hhu.%hhu.%hhu", &c_ip[3], &c_ip[2], &c_ip[1], &c_ip[0]);

            return ip_address4(ip);
        }
        //-----
        ip_address6::ip_address6(unsigned short addr[16], long scopid  ) 
            :  ip_address_base(AddrFamily::InternetV6),  m_scopid(0) {
            if(addr == 0) return;
               
            for (int i = 0; i < 8; i++) {
                m_numbers[i] = (unsigned short)(addr[i * 2] * 256 + addr[i * 2 + 1]);
            }
            m_scopid = scopid;
        }
        ip_address6::ip_address6(unsigned short addr[16])  
            : ip_address_base(AddrFamily::InternetV6), m_scopid(0) {
            for (int i = 0; i < 8; i++) {
                m_numbers[i] = (unsigned short)(addr[i * 2] * 256 + addr[i * 2 + 1]);
            }
        }
        ip_address6::ip_address6(const ip_address6& v) 
            : ip_address_base(v.getFamily()), m_scopid(v.m_scopid) {
            for(int i =0; i < 8; i++)
                m_numbers[i] = v.m_numbers[i];            
        }
        long ip_address6::getscopid() {
                return m_scopid;
        }
        void ip_address6::setscopid(long id) {
            if(m_scopid != id) {
                m_scopid = id;
            }
        }
        void ip_address6::getaddress(unsigned short b[16]) {
            for(int i=0, j =0; i < 8; i++){
                b[j++] = (unsigned char)((m_numbers[i] >> 8) & 0xFF);
                b[j++] = (unsigned char)((m_numbers[i]     ) & 0xFF);
            }
        } 
        ip_address6& ip_address6::operator = (const ip_address6& v) {
            for(int i =0; i < 8; i++)
                m_numbers[i] = v.m_numbers[i];     
            m_scopid = v.m_scopid;
            return *this;
        }
        ip_address6::ip_address6(const ip_address4& v) {
            m_numbers[0] = m_numbers[1] = m_numbers[2] = m_numbers[3] = m_numbers[4] = 0;  
            m_numbers[5] = 0xFFFF;
            m_numbers[6] = (unsigned short)(((v.get() & 0x0000FF00) >> 8) | ((v.get() & 0x000000FF) << 8));
            m_numbers[7] = (unsigned short)(((v.get() & 0xFF000000) >> 24) | ((v.get() & 0x00FF0000) >> 8));
            
            m_scopid = 0;            
        }
        const ip_address4& ip_address6::to_ip4() {
            long address = ((((uint32_t)m_numbers[6] & 0x0000FF00u) >> 8) | (((uint32_t)m_numbers[6] & 0x000000FFu) << 8)) |
                    (((((uint32_t)m_numbers[7] & 0x0000FF00u) >> 8) | (((uint32_t)m_numbers[7] & 0x000000FFu) << 8)) << 16);
 
            return ip_address4(address);
        }
            
    }
}
