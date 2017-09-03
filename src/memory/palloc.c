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
#include "inttypes.h"
#include "stdio.h"

#include "../include/memory/palloc.h"

palloc_t pmm_alloced[PALLOC_MAX_BLOCKS];
unsigned pmm_bitmap[MAX_PALLOC];
unsigned pmm_page_number;
uint64_t pmm_total;

void pfree(void* addr) {
    unsigned x, y;
    for(uint64_t i=0; i < PALLOC_MAX_BLOCKS; i++) {
        if(pmm_alloced[i].mem == addr) {
            x = ((unsigned)addr/4096) / 32;
            y = ((unsigned)addr/4096) % 32;
            pmm_bitmap[x] = pmm_bitmap[x] - (1 << y);
            for(uint64_t j = 1; j < pmm_alloced[i].dim; j++) {
                if(y == 31) {
                    y = 0; x++;
                } else {
                    y++;
                }
                 pmm_bitmap[x] = pmm_bitmap[x] - (1 << y);
            }
            pmm_alloced[i].dim = 0;
        }
    }
}
uint8_t pisfree(int *x, int *y) {
    if(*y == 31) {
        *y = 0;
        *x = *x + 1;
    } else {
        *y = *y + 1;
    }
    return ((pmm_bitmap[(int)*x] & (1 << (int)*y)) == 1)? 0 : 1;
}
uint64_t palloc_first() {
    for(uint64_t x; x < PALLOC_MAX_BLOCKS; x++) {
        if(pmm_alloced[x].dim == 0)
            return x;
    }
    return -1;
}
void* palloc(size_t size) {
    unsigned addr, x, y, j, k;
    int a, b, ff;
    
    for(x = 0; x < (pmm_page_number/32); x++) {
        for (y = 0;y <32; y++) {
            if((pmm_bitmap[x] & (1<<y)) == 0) {
                a = x; b = y;
                for(j = 0; j <= size; j++ ) {
                    if(j==size) {
                        pmm_bitmap[x] = pmm_bitmap[x] + (1<<y);
                        for(k = 1; k < size; k++) {
                            if(y == 31) {
                                y = 0;
                                x++;
                            } else {
                                y++;
                            }
                             pmm_bitmap[x] = pmm_bitmap[x] + (1<<y);
                        }
                        addr = (x)*(1024 * 32 * PALLOC_SIZE) + (y*1024*PALLOC_SIZE);
                        ff = palloc_first();
                        pmm_alloced[ff].dim = size;
                        pmm_alloced[ff].mem = (void*)addr;
                        return (void*)addr;
                    }
                    if(pisfree(&a, &b)) {
                        x = a;
                        y = b;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
uint64_t ptotalsize() {
    return pmm_total;
}
uint64_t pgetusable(void* addr) {
    for(int i = 0; i < PALLOC_MAX_BLOCKS; i++) {
        if(pmm_alloced[i].mem == addr)
            return pmm_alloced[i].dim;
    }
    return 0;
}
uint64_t pgetfree() {
    unsigned y,x,np = 0;
    for(x =0; x < pmm_page_number; x++) {
        for (y=0; y < 32; y++) {
            if((pmm_bitmap[x] & (1 << y) ) == 0)
                np++;
        }
    }
    return np;
}
uint64_t pusedmem() {
    return ((pmm_page_number - pgetfree()) * PALLOC_SIZE);
}
void pinit(uint64_t memsize) {
    
    pmm_total = memsize;
    pmm_page_number = ((((unsigned) pmm_total / PALLOC_SIZE) / 32) * 32);
    for(unsigned x = 0; x < (pmm_page_number/32) ; x++) 
        pmm_bitmap[x] = 0;
    for(unsigned x = 0; x < PALLOC_MAX_BLOCKS; x++) {
        pmm_alloced[x].dim = 0;
    }
        
}