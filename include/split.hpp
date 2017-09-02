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
 * File:   split.hpp
 * Author: annas
 *
 * Created on 7. November 2016, 23:41
 */

#ifndef __SPLIT_H
#define __SPLIT_H

// functions to split a string by a specific delimiter
#include "string.hpp"
#include "vector.hpp"
#include <string.h>

namespace std
{
	std::vector<std::string> split(std::string&  strString, const char*  delimiter);
	
	template<typename T, class StringT>
	void tokenize(T* s, T delim, std::vector<StringT>& container)
	{
		const T *olds = s;
		T olddelim = delim;

		while(olddelim && *s) 
		{
			while(*s && (delim != *s)) s++;
			*s ^= olddelim = *s; 
			container.push_back(StringT(olds));
			*s++ ^= olddelim; 
			olds = s;
		}
	}
}

#endif


