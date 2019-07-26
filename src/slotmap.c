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

// This code is based on
// https://github.com/seanmiddleditch/TinyExperiments/blob/master/SlotMapExample/Main.cpp
// Credit: seanmiddleditch

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "slotmap.h"


/**
 * Create a new slot map.
 * 
 * @returns The new slot map.
 */
Slotmap sm_new()
{
    Slotmap sm;
    sm.free_stack = stack_new(sizeof(sm_item_id), 0);
    sm.chunk_stack = stack_new(__SIZEOF_POINTER__, 0);

    return sm;
}


sm_item_id sm_create_item(Slotmap* sm)
{

    if (sm->free_stack.size == 0) {
        // TODO(safety): Check calloc and warn if fail
        SMItem* chunk = calloc(SM_CHUNK_SIZE, sizeof(SMItem));

        // TODO(reading): Why reversed order here? Better memory access?
        for(int ii = SM_CHUNK_SIZE-1; ii >= 0; --ii) {
            chunk[ii].id = sm->chunk_stack.size * SM_CHUNK_SIZE + ii;
            stack_push(&(sm->free_stack), &(chunk[ii].id));
        }

        stack_push(&(sm->chunk_stack), chunk);
    }

    return *(sm_item_id *)stack_pop(&sm->free_stack);
}

SMItem* sm_get_item(Slotmap* sm, sm_item_id id)
{
    SMItem* item = (SMItem *)&sm->chunk_stack.data[(id & 0xFFFFFFFF) / SM_CHUNK_SIZE] + ((id & 0xFFFFFFFF) % SM_CHUNK_SIZE);
    return item->id != id ? NULL : item;
}


/**
 * Destroy the slot map and free associated memory.
 * 
 * @param sm   Pointer to the slot map
 */
void sm_destroy(Slotmap* sm)
{
    stack_destroy(&sm->free_stack);

    for (size_t ii=0; ii < sm->chunk_stack.size; ++ii)
        free(((SMItem **)sm->chunk_stack.data)[ii]);

    stack_destroy(&sm->chunk_stack);
}
