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
 * File:   type_traits.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 00:26
 */

#ifndef _STD_TYPETRAITS_H_
#define _STD_TYPETRAITS_H_

//#include "iostream.hpp"


namespace std
{
        template <class ...ts> struct make_void { typedef void type; };
        template <class ...ts> using void_t = typename make_void<ts ...>::type;
        
        template<class T, T v> struct integral_constant {
            enum {
                value = v
            };
        };
        typedef integral_constant<bool, true> true_type;
        typedef integral_constant<bool, false> false_type;
        
        template<typename T> struct is_enum
          : public integral_constant<bool, __is_enum(T)> { };

        template<typename T> struct is_union
          : public integral_constant<bool, __is_union(T)> { };

        template<typename T> struct is_class 
            : public integral_constant<bool, __is_class(T)> { };
        template<typename> struct is_function 
            : public false_type { };
        
        template<typename T> struct is_empty
            : public integral_constant<bool, __is_empty(T)> { };
        
        template<typename T> struct is_abstract
            : public integral_constant<bool, __is_abstract(T)> { };
        
        template<typename T> struct is_polymorphic
            : public integral_constant<bool, __is_polymorphic(T)> { };
            
        template<typename T> struct is_literal_type 
            : public integral_constant<bool, __is_literal_type(T)> { };
            
        template<typename T> struct is_pod 
            : public integral_constant<bool, __is_pod(T)> { };
            
        

	template<typename T> struct is_integral 
            : public integral_constant<bool, false> { };
	template<class T> struct is_integral<const T> 
            : public is_integral<T> { };
        template<class T> struct is_integral<volatile T>
            : public is_integral<T> { };
        template<class T> struct is_integral<const volatile T> 
            : public is_integral<T> { };
        
        #define STL_INTEGRAL(T) template<> struct is_integral<T> \
                            : public integral_constant<bool, true> { };
	STL_INTEGRAL(char);
	STL_INTEGRAL(unsigned char);
	STL_INTEGRAL(short);
	STL_INTEGRAL(unsigned short);
	STL_INTEGRAL(int);
	STL_INTEGRAL(unsigned int);
	STL_INTEGRAL(long);
	STL_INTEGRAL(unsigned long);
	STL_INTEGRAL(wchar_t);
        STL_INTEGRAL(bool);

        template<typename T> struct is_rational
            : public integral_constant<bool, false> { };
	template<class T> struct is_rational<const T> 
            : public is_rational<T> { };
        template<class T> struct is_rational<volatile T>
            : public is_rational<T> { };
        template<class T> struct is_rational<const volatile T> 
            : public is_rational<T> { };
        
        #define STL_RATIONAL(T) template<> struct is_rational<T> \
                            : public integral_constant<bool, true> { };
        STL_RATIONAL(float);
        STL_RATIONAL(double);
        STL_RATIONAL(long double);
        
        template<typename T> struct is_void
            : public integral_constant<bool, false> { };
	template<class T> struct is_void<const T> 
            : public is_void<T> { };
        template<class T> struct is_void<volatile T>
            : public is_void<T> { };
        template<class T> struct is_void<const volatile T> 
            : public is_void<T> { };
        
        #define STL_VOIDTYPE(T) template<> struct is_void<T> \
                            : public integral_constant<bool, true> { };
        STL_VOIDTYPE(void);
        STL_VOIDTYPE(const void);
        STL_VOIDTYPE(volatile void );
        STL_VOIDTYPE(const volatile void );
        
        template<typename T> struct is_floating_point 
            : public integral_constant<bool, false> { };
            
	template<> struct is_floating_point<float> 
             : public integral_constant<bool, true> { };
	template<> struct is_floating_point<double>
            : public integral_constant<bool, true> { };

	template<typename T> struct is_pointer 
            : public integral_constant<bool, false> { };
            
        template<typename T> struct is_pointer<T*>
            : public integral_constant<bool, true> { };

	template<typename T> struct is_fundamental
            : public integral_constant<bool,  is_integral<T>::value || is_rational<T>::value> { };
	

	template<typename T> struct has_trivial_constructor
            : public integral_constant<bool,  is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };
	


	template<typename T> struct has_trivial_copy
            : public integral_constant<bool, is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };
	
	

	template<typename T> struct has_trivial_assign
            : public integral_constant<bool, is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };
	

	template<typename T> struct has_trivial_destructor
            : public integral_constant<bool, is_fundamental<T>::value || is_pointer<T>::value || is_pod<T>::value> { };
	

	template<typename T> struct has_cheap_compare
           : public integral_constant<bool, has_trivial_copy<T>::value && sizeof(T) <= 4 > { };

        
       
        
      
        
        
        
} 

#endif 

