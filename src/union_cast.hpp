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

#ifndef __ASSTL_UNION_CAST_HPP__
#define __ASSTL_UNION_CAST_HPP__

namespace std {
  template <typename Tto, typename Tfrom> Tto union_cast(Tfrom value) { union { Tfrom v; Tto to; } y = {value}; return y.to;  } 
  
  template <typename Tto, int8_t>     Tto union_cast(int8_t value) { union { int8_t v; Tto to; } y = {value}; return y.to;  }  
  template <typename Tto, int16_t>    Tto union_cast(int16_t value) { union { int16_t v; Tto to; } y = {value}; return y.to;  }  
  template <typename Tto, int32_t>    Tto union_cast(int32_t value) { union { int32_t v; Tto to; } y = {value}; return y.to;  }  
  
  template <typename Tto, uint8_t>    Tto union_cast(uint8_t value) { union { uint8_t v; Tto to; } y = {value}; return y.to;  }  
  template <typename Tto, uint16_t>   Tto union_cast(uint16_t value) { union { uint16_t v; Tto to; } y = {value}; return y.to;  }  
  template <typename Tto, uint32_t>   Tto union_cast(uint32_t value) { union { uint32_t v; Tto to; } y = {value}; return y.to;  }  

  template <typename Tto, void*>      Tto union_cast(void* value) { union { void* v; Tto to; } y = {value}; return y.to;  }  
   
  template <typename Tto>             Tto union_cast(float value) { union { float v; Tto to; } y = {value}; return y.to; }
  template <typename Tto>             Tto union_cast(double value) { union { double v; Tto to; } y = {value}; return y.to; }
}

#endif
