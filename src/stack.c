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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

/**
 * Create a new stack.
 * 
 * @param element_size      The size of each element as returned by `sizeof()`
 * @param initial_capacity  The initial capacity
 * 
 * @returns The new stack
 */
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


/**
 * Push a new item to the end of the stack.
 * 
 * @param stack   Pointer to the stack
 * @param item    Pointer to the item (must have size equal to `element_size`)
 * 
 * @returns       0 if successful, -1 otherwise
 */
int stack_push(Stack* st, void* item)
{
    if ((st->size+1) > st->capacity) {
        st->capacity = (size_t)(st->capacity * STACK_GROWTH_FACTOR);

        if (st->capacity < 2)
            st->capacity = 2;

        void* old = st->data;
        st->data = realloc(st->data, st->capacity * st->element_size);
        if (st->data == NULL) {
            st->data = old;
            fprintf(stderr, "Failed to realloc stack!\n");
            return -1;
        }
    }

    memcpy((char *)st->data + st->element_size * (st->size++), (char *)item, st->element_size);
    return 0;
}


/**
 * Pop an item from the end of the stack and remove it.
 * 
 * @param stack   Pointer to the stack
 * 
 * @returns       Pointer to the popped item which should be dereferenced
 *                or memcpy'd IMMEDIATELY by the user as the validity of the pointer can
 *                no longer be gauranteed after any other stack methods are called.
 */
void* stack_pop(Stack* st)
{
    return (char *)st->data + st->element_size * (--st->size);
}


/**
 * Compress the stack to free unused memory.
 * 
 * @param stack   Pointer to the stack
 * 
 * @returns       0 if successful, -1 otherwise
 */
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


/**
 * Destroy the stack and free the data.
 * 
 * @param stack   Pointer to the stack
 */
void stack_destroy(Stack* st)
{
    st->size = 0;
    st->element_size = 0;
    st->capacity = 0;

    // free the data
    free(st->data);
    st->data = NULL;
}
