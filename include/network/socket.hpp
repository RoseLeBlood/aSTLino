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
 * File:   socket.hpp
 * Author: annas
 *
 * Created on 26. Dezember 2016, 21:38
 */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "endpoint.hpp"
#include "../common.hpp"


namespace std {
    namespace net {
        
        struct SocketInformation {
            SocketInformationOptions Options;
            
            ProcType    Proctocol;
            AddrFamily  AdressFamily;
            SocketTyp   Type;
            bool        IsBound;
        };
        
        template<class TIPAddress>
        class socket {
            const int SOCKET_CLOSE_CODE = 1004;
        public:
            using Ipaddr_t = TIPAddress;
            using endpoint_t = end_point<Ipaddr_t>;
            
            property<ProcType, socket>   Proctocol
                {this, &socket::getProcType, &socket::setProcType};
            property<AddrFamily, socket> AdressFamily
                {this, &socket::getAddrFamily, &socket::setAddrFamily};
            property<SocketTyp, socket> Typ
                {this, &socket::getSocketTyp, &socket::setSocketTyp};
            property<bool, socket> DontFragment
                {this, &socket::getDontFragment, &socket::setDontFragment};
            property<bool, socket> DualMode
                {this, &socket::getDualMode, &socket::setDualMode};  
            property<bool, socket> NoDelay
                {this, &socket::getNoDelay, &socket::setNoDelay};
                
            socket(SocketInformation info) {
                m_addrFamily = info.AdressFamily;
                m_procType = info.Proctocol;
                m_skTyp = info.Type;
                m_isBound = info.IsBound;
                
                m_isListing = (info.Options & SocketInformationOptions::Listing) != 0;
                m_isConnected = (info.Options & SocketInformationOptions::Conected) != 0;
                m_usedOverlappedIO  = (info.Options & SocketInformationOptions::UseOnlyOverlappedIO) != 0;
                m_isBloking = (info.Options & SocketInformationOptions::NonBlocking) == 0;
                
                InitializeSockets();
                SocketDefaults();
            }
            socket(AddrFamily addr, SocketTyp sockt, ProcType ptyp) {
                m_addrFamily = addr;
                m_skTyp = sockt;
                m_procType = ptyp;
                m_isConnected = true;
                InitializeSockets();
            }
            static socket<Ipaddr_t>* Accept() {
                
            }
            void Bind(const endpoint_t& localEndPoint) {
                
                int error = 0;
                // internal error =...
                
                if(error == 0) m_isBound = true;
                m_seedEndPoint = localEndPoint;
            }
            void Listen(int backlog) {
                
                m_isListing = true;
            }
            void Connect(Ipaddr_t ipaddr, const int port) {
                
            }
            void Connect(std::string addr, const int port) {
                
            }
            void Connect(const endpoint_t& ep) {
                
            }
            void Disconnect(const bool b) {
                
            }
            void shutdown(const int flags) {
                
            }
        public: // read write
            size_t receive(void *data, size_t offset, size_t size, 
                    const SocketFlags& flags, SocketError& error) {
                
            }
            size_t receivefrom(void *data, size_t offset, size_t size, 
                    const SocketFlags& flags, endpoint_t ep) {
                
            }
            size_t send(void *data, size_t offset, size_t size, 
                    const SocketFlags& flags, SocketError& error) {
                
            }
            size_t sendto(void *data, size_t offset, size_t size, 
                    const SocketFlags& flags, endpoint_t ep) {
                
            }
        protected:
            void SocketDefaults() {
                try {
                    if(m_addrFamily == AddrFamily::Internet) {
                        DontFragment = false;
                        if(m_procType == ProcType::TCP)
                            NoDelay = false;
                    } else if(m_addrFamily == AddrFamily::InternetV6 )
                        DualMode = true;
                } catch(...) {
                    
                }
            }
            void InitializeSockets() {
                //std::Sys::sCreate(....);
            }
        protected:
            ProcType getProcType() { return m_procType; }
            AddrFamily getAddrFamily() { return m_addrFamily; }
            SocketTyp getSocketTyp() { return m_skTyp; }
            
            void setProcType(const ProcType v) { m_procType; }
            void setAddrFamily(const AddrFamily v) {  m_addrFamily; }
            void setSocketTyp(const SocketTyp v) {  m_skTyp; }
            
            bool getDontFragment() {
                
            }
            void setDontFragment(const bool v) {
                
            }
            bool getDualMode() {
                
            }
            void setDualMode(const bool v) {
                
            }
            bool getNoDelay() {
                
            }
            void setNoDelay(const bool v) {
                
            }
            endpoint_t* getLocalEndPoint() {
                if(m_seedEndPoint == 0) return 0;
                
                int error =0;
               // AddrFamily s = std::Sys::sGetEndPoint(void*, m_addrFamily, error);
                //return m_seedEndPoint.Create(s);
            }
            endpoint_t* getRemoteEndPoint() {
                if(m_seedEndPoint == 0 && !m_isConnected) return 0;
                
                int error =0;
               // AddrFamily s = std::Sys::sGetRemoteEndPoint(void*, m_addrFamily, error);
                //return m_seedEndPoint.Create(s);
            }
        private:
            ProcType m_procType;
            AddrFamily m_addrFamily;
            SocketTyp  m_skTyp;
            
            endpoint_t m_eEndPoint;
            bool m_isClosing;
            bool m_isListing;
            bool m_usedOverlappedIO;
            bool m_isBloking;
            bool m_isBound;
            bool m_isConnected;
            
            int m_iTimeout;
            int m_iCleanedUp;
            bool ConnProgress;
            
            endpoint_t* m_seedEndPoint;
        };
    }
}


#endif /* SOCKET_HPP */

