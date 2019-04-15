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

#include <stdlib.h>
#include <string.h>
#include "stack.h"

STACK_NAME()* STACK_NAME(new)(const size_t initial_capacity)
{
    STACK_NAME()* st = malloc(sizeof(STACK_NAME()));
    st->size = 0;
    st->capacity = initial_capacity;
    st->data = malloc(sizeof(STACK_ITEM_TYPE) * initial_capacity);

    return st;
}


void STACK_NAME(push)(STACK_NAME()* st, const STACK_ITEM_TYPE item)
{
    st->size += 1;
    if (st->size > st->capacity) {
        st->capacity = (size_t)(st->capacity * STACK_GROWTH_FACTOR);
        st->data = reallocf(st->data, st->capacity * sizeof(STACK_ITEM_TYPE));
    }

    st->data[st->size] = item;
}


STACK_ITEM_TYPE STACK_NAME(pop)(STACK_NAME()* st)
{
    STACK_ITEM_TYPE item = st->data[st->size];
    memset(&(st->data[st->size]), 0, sizeof(STACK_ITEM_TYPE));
    st->size -= 1;
    return item;
}


void STACK_NAME(destroy)(STACK_NAME()* st)
{
    // free the data
    free(st->data);
    st->data = NULL;

    // free the stack itself
    free(st);
}
