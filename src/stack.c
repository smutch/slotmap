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
#include <stdio.h>
#include "stack.h"

Stack stack_new(const size_t element_size, const size_t initial_capacity)
{
    Stack st;
    st.element_size = element_size;
    st.size = 0;
    st.capacity = initial_capacity;

    st.data = calloc(initial_capacity, element_size);
    if (st.data == NULL) {
        fprintf(stderr, "Failed to malloc stack!\n");
        st.element_size = 0;
        st.capacity = 0;
    }

    return st;
}


int stack_push(Stack* st, void* item)
{
    st->size += 1;
    if (st->size > st->capacity) {
        st->capacity = (size_t)(st->capacity * STACK_GROWTH_FACTOR);

        void* old = st->data;
        st->data = realloc(st->data, st->capacity * st->element_size);
        if (st->data == NULL) {
            st->data = old;
            fprintf(stderr, "Failed to realloc stack!\n");
            return -1;
        }
    }

    memcpy(st->data + st->element_size * st->size, item, st->element_size);
    return 0;
}


void* stack_pop(Stack* st)
{
    return st->data + st->element_size * (st->size--);
}


int stack_compress(Stack* st)
{
    void *old = st->data;
    st->data = realloc(st->data, st->size * st->element_size);
    if (st->data == NULL) {
        st->data = old;
        fprintf(stderr, "Failed to realloc stack!\n");
        return -1;
    }

    st->capacity = st->size;
    return 0;
}


void stack_destroy(Stack* st)
{
    st->size = 0;
    st->element_size = 0;
    st->capacity = 0;

    // free the data
    free(st->data);
    st->data = NULL;
}
