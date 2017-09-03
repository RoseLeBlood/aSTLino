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
 * File:   isaac_engine.hpp
 * Author: annas
 *
 * Created on 22. Dezember 2016, 19:20
 */

#ifndef ISAAC_ENGINE_HPP
#define ISAAC_ENGINE_HPP

namespace std 
{
    template <class TIntType, size_t size, TIntType TGoldenRatio>
    class isaac_engine {
    public:
        using result_type = TIntType;
        static constexpr result_type golden_ratio = result_type(TGoldenRatio);
        
        isaac_engine(result_type a=0, result_type b=0, result_type c =0) {
            seed(a,b,c);
        }
        void seed(result_type a, result_type b, result_type c, result_type s =((void*)0)) {
            result_type a,b,c,d,e,f,g,h;
            a = b = c = d = e = f = g = h = golden_ratio;
            
            for(int i = 0; i < 256; i++) {
                m_rsl[i] = s != ((void*)0) ? s[i] : 0;
            }
            m_a = a;
            m_b = b;
            m_c = c;
            
            shuffle(a,b,c,d,e,f,g,h);
            shuffle(a,b,c,d,e,f,g,h);
            shuffle(a,b,c,d,e,f,g,h);
            shuffle(a,b,c,d,e,f,g,h);
            
          
            for(result_type i=0; i < 256; i+=8) {
                    a+= (m_rsl)[i  ]; b+=(m_rsl)[i+1]; c+=(m_rsl)[i+2]; d+=(m_rsl)[i+3];
                    e+= (m_rsl)[i+4]; f+=(m_rsl)[i+5]; g+=(m_rsl)[i+6]; h+=(m_rsl)[i+7];
         
                    shuffle(a,b,c,d,e,f,g,h);
         
                    (m_mem)[i  ]=a; (m_mem)[i+1]=b; (m_mem)[i+2]=c; (m_mem)[i+3]=d;
                    (m_mem)[i+4]=e; (m_mem)[i+5]=f; (m_mem)[i+6]=g; (m_mem)[i+7]=h;
                
            }  
            for(result_type i=0; i < 256; i += 8) {
                    a+=(m_mem)[i  ]; b+=(m_mem)[i+1]; c+=(m_mem)[i+2]; d+=(m_mem)[i+3];
                    e+=(m_mem)[i+4]; f+=(m_mem)[i+5]; g+=(m_mem)[i+6]; h+=(m_mem)[i+7];
         
                    shuffle(a,b,c,d,e,f,g,h);
         
                    (m_mem)[i  ]=a; (m_mem)[i+1]=b; (m_mem)[i+2]=c; (m_mem)[i+3]=d;
                    (m_mem)[i+4]=e; (m_mem)[i+5]=f; (m_mem)[i+6]=g; (m_mem)[i+7]=h;
            } 
            isaac();
            m_cnt = 255;
        }
        void discard(unsigned long long z) {
            for (; z != 0ULL; --z)
                (*this).operator ()();
        } 
        result_type operator()() {
            return(!m_cnt-- ? (isaac(), m_cnt=(255), m_rsl[m_cnt]) :
                                  m_rsl[m_cnt]);
        }
        static constexpr result_type min() { return 0; }  
        static constexpr result_type max() { return (size == 64) ? UINT64_MAX : UINT32_MAX; }  
    private:
        void shuffle(result_type& a, result_type& b, result_type& c, result_type& d,
                result_type& e, result_type& f, result_type& g, result_type& h){
            if(size == 32){
                a^=b<<11; d+=a; b+=c; 
                b^=c>>2;  e+=b; c+=d; 
                c^=d<<8;  f+=c; d+=e; 
                d^=e>>16; g+=d; e+=f; 
                e^=f<<10; h+=e; f+=g; 
                f^=g>>4;  a+=f; g+=h; 
                g^=h<<8;  b+=g; h+=a; 
                h^=a>>9;  c+=h; a+=b; 
            } else if (size == 64) {
                a-=e; f^=h>>9;  h+=a;
                b-=f; g^=a<<9;  a+=b;
                c-=g; h^=b>>23; b+=c;
                d-=h; a^=c<<15; c+=d;
                e-=a; b^=d>>14; d+=e;
                f-=b; c^=e<<20; e+=f;
                g-=c; d^=f>>17; f+=g;
                h-=d; e^=g<<14; g+=h;
            }
        }
        result_type ind(result_type* mm, result_type x) {
            if(size == 32) 
                return (*(result_type*)((unsigned char*)(mm) + ((x) & ((255)<<2))));
            else if(size == 64)
                 return (*(result_type*)((unsigned char*)(mm) + ((x) & ((255)<<3))));
        }
        void rngstep(result_type mix, result_type& a, result_type& b,
                     result_type*& mm, result_type*& m, result_type*& m2,
                     result_type*& r, result_type& x, result_type& y) {
            x = *m;  
            a = (a^(mix)) + *(m2++); 
            *(m++) = y = ind(mm,x) + a + b; 
            *(r++) = b = ind(mm,y>>8) + x;
        }
        void isaac() {
            result_type x,y;
            result_type* mm = m_mem;
            result_type* r  = m_rsl;
            result_type a = (m_a);
            result_type b = (m_b + (++m_c));
   
            result_type* m    = mm; 
            result_type* m2   = (m+(128));
            result_type* mend = m2;
            
            for(; m<mend; ){
                if(size == 32) {
                    rngstep((a<<13), a, b, mm, m, m2, r, x, y);
                    rngstep((a>>6) , a, b, mm, m, m2, r, x, y);
                    rngstep((a<<2) , a, b, mm, m, m2, r, x, y);
                    rngstep((a>>16), a, b, mm, m, m2, r, x, y);
                } else {
                    rngstep(~(a^(a<<21)), a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a>>5)  , a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a<<12) , a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a>>33) , a, b, mm, m, m2, r, x, y);
                }
            }
            m2 = mm;
            for(; m2<mend; ) {
                if(size == 32) {
                    rngstep((a<<13), a, b, mm, m, m2, r, x, y);
                    rngstep((a>>6) , a, b, mm, m, m2, r, x, y);
                    rngstep((a<<2) , a, b, mm, m, m2, r, x, y);
                    rngstep((a>>16), a, b, mm, m, m2, r, x, y);
                } else {
                    rngstep(~(a^(a<<21)), a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a>>5)  , a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a<<12) , a, b, mm, m, m2, r, x, y);
                    rngstep(  a^(a>>33) , a, b, mm, m, m2, r, x, y);
                }
            }
            m_b = b;
            m_a = a;
        }
    private:
        TIntType m_cnt;
        TIntType m_rsl[256];
        TIntType m_mem[256];
        TIntType m_a;
        TIntType m_b;
        TIntType m_c;
    };
}


#endif /* ISAAC_ENGINE_HPP */

