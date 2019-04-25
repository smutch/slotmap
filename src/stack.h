/*=====================================================================
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
=====================================================================*/

#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/**
 * The factor by which the number of elements in the stack is increased if
 * capacity is reached.
 */
#define STACK_GROWTH_FACTOR 1.5

/**
 * The Stack structure.
 */
typedef struct stack {
    /** The data */
    void* data;
    /** The size of each element in the stack (from `sizeof()`) */
    size_t element_size;
    /** The current size of the stack */
    size_t size;
    /** The maximum capacity with the current memory allocation */
    size_t capacity;
} Stack;

Stack stack_new(const size_t element_size, const size_t initial_capacity);
int stack_push(Stack* st, void* item);
void* stack_pop(Stack* st);
int stack_compress(Stack* st);
void stack_destroy(Stack* st);

#endif
