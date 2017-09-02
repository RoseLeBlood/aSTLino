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
 * File:   utils.hpp
 * Author: annas
 *
 * Created on 13. November 2016, 01:22
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#define DEG2RAD  (3.141593 / 180.0)
#define RAD2DEG  (180.0 / 3.141593)
#define EPSILON  0.00001
 
#include "../algorithm.hpp"

#define PI 3.14159265358979323846
#define PIOverTwo (PI / 2)
#define PIOverFour (PI / 4)
#define TwoPI (PI * 2)
#define Log10E (0.4342944819032f)
#define Log2E (1.442695040888f)


namespace std
{
    namespace math
    {
        template <typename T>
        inline T factorial(T p)
        {
            if ( p == 0 || p == 1 ) return 1;
            else if ( p < 0 ) return 0;

            T f = 1;
            for(; p > 1; p--) f *= p;
              
            return f;
        }
        template <typename T>
        inline T barycentric(T value1, T value2, T value3, T amount1, T amount2)
	{
            return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
	}
        template <typename T>
	inline T catmullrom(T value1, T value2, T value3, T value4, T amount)
	{
            float amountSq = amount * amount;
            float amountCube = amountSq * amount;
            return (( T(2.0) * value2 +
			(-value1 + value3) * amount +
			((T)2.0 * value1 - (T)5.0 * value2 + (T)4.0 * value3 - value4) * amountSq +
			((T)3.0 * value2 - (T)3.0 * value3 - value1 + value4) * amountCube) * (T)0.5);
	}
	template <typename T>	
        inline T clamp (T value, T min, T max)
	{
            return std::_min<T> (std::_max<T> (min, value), max);
	}
        template <typename T>	
        inline T hermite (T value1, T tangent1, T value2, T tangent2, T amount)
	{
            T s = amount;
            T s2 = s * s;
            T s3 = s2 * s;
            T h1 =  2 * s3 - 3 * s2 + 1;
            T h2 = -2 * s3 + 3 * s2;
            T h3 =      s3 - 2 * s2 + s;
            T h4 =      s3 -     s2;
            return value1 * h1 + value2 * h2 + tangent1 * h3 + tangent2 * h4;
	}

        template <typename T>	
        inline T Lerp (T value1, T value2, T amount)
	{
		return value1 + (value2 - value1) * amount;
	}
        template <typename T>	
        inline T SmoothStep (T value1, T value2, T amount)
	{
            amount = amount * amount * ((T)3 - (T)2 * amount);
            return value1 + (value2 - value1) * amount;
	}

		
		
		
			
    }
}


#endif /* UTILS_HPP */

