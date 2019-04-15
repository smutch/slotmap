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

#ifndef STACK_H
#define STACK_H

#ifndef STACK_ITEM_TYPE
#define STACK_ITEM_TYPE int
#endif

#define STACK_FUNC(name) STACK_ITEM_TYPE_stack_##name

#include <stddef.h>

typedef struct stack {
    STACK_ITEM_TYPE* data;
    size_t size;
    size_t capacity;
} Stack;

Stack* STACK_FUNC(new)(size_t initial_capacity);
void STACK_FUNC(push)(Stack* st, STACK_ITEM_TYPE item);
STACK_ITEM_TYPE STACK_FUNC(pop)(Stack* st);

#endif
