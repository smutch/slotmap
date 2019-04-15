/**********************************************************************
A basic slot map for C
Copyright © 2019 Simon Mutch

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************/

#ifndef STACK_TYPE
#define STACK_TYPE int
#endif

#ifndef STACK_H
#define STACK_H

#define STACK_GROWTH_FACTOR 1.5

#define CONCAT_I(a, b) a##_##b
#define CONCAT(a, b) CONCAT_I(a, b)
#define STACK_NAME(x) CONCAT(CONCAT(STACK_TYPE, stack), x)

#include <stddef.h>

typedef struct STACK_NAME() {
    STACK_TYPE* data;
    size_t size;
    size_t capacity;
} STACK_NAME();

STACK_NAME()* STACK_NAME(new)(const size_t initial_capacity);
int STACK_NAME(push)(STACK_NAME()* st, const STACK_TYPE item);
STACK_TYPE STACK_NAME(pop)(STACK_NAME()* st);
int STACK_NAME(compress)(STACK_NAME()* st);
void STACK_NAME(destroy)(STACK_NAME()* st);

#endif
