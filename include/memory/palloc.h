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
 * File:   palloc.h
 * Author: annas
 *
 * Created on 22. April 2017, 23:31
 */

#ifndef PALLOC_H
#define PALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PALLOC 1048576
#define PALLOC_SIZE 4
#define PALLOC_MAX_BLOCKS (MAX_PALLOC / 32)

typedef struct {
    void* mem;
    size_t dim;
} palloc_t;

/// @brief initialis the fixed block allocator with 512MB 
/// @param memsize The used memory
void pinit(uint64_t memsize);
/// @brief allocated memory 
/// @param size The to allocated memory
void* palloc(size_t size);
/// @brief DeAlloceted the memory
/// @param addr The Memory to dealloceted
void pfree(void* addr);

/// @brief get the total memory size 
uint64_t ptotalsize();
/// @brief get the to usable size of memory
/// @param m The to testing memory 
uint64_t pgetusable(void* m);
/// @brief get thebused memory
uint64_t pusedmem();
#ifdef __cplusplus
}
#endif

#endif /* PALLOC_H */

