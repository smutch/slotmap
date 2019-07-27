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
    sm.free_stack = stack_new(sizeof(int), 0);
    sm.chunk_stack = stack_new(__SIZEOF_POINTER__, 0);

    return sm;
}


/**
 * Create a 'new' item in the slotmap.  We allocate a new chunk if necessary, or simply return the next free item.
 * 
 * @param sm   Pointer to the slot map
 *
 * @returns    Pointer to new item
 */
SMItem* sm_create_item(Slotmap* sm)
{

    if (sm->free_stack.size == 0) {
        // TODO(safety): Check calloc and warn if fail
        SMItem* chunk = calloc(SM_CHUNK_SIZE, sizeof(SMItem));

        for(int ii = SM_CHUNK_SIZE-1; ii >= 0; --ii) {
            chunk[ii].id = sm->chunk_stack.size * SM_CHUNK_SIZE + ii;
            stack_push(&(sm->free_stack), &(chunk[ii].id));
        }

        stack_push(&(sm->chunk_stack), &chunk);
    }

    int next_free = *(int *)stack_pop(&(sm->free_stack));
    return &((SMItem**)(sm->chunk_stack.data))[next_free / SM_CHUNK_SIZE][next_free % SM_CHUNK_SIZE];
}


/**
 * Get an item from the slotmap.
 * 
 * @param sm   Pointer to the slot map
 * @param id   Item ID to retrieve
 *
 * @returns    Pointer to item if successful, NULL otherwise.
 */
SMItem* sm_get_item(Slotmap* sm, sm_item_id id)
{
    SMItem* item = ((SMItem **)(sm->chunk_stack.data))[(id & 0xFFFFFFFF) / SM_CHUNK_SIZE] + ((id & 0xFFFFFFFF) % SM_CHUNK_SIZE);
    return item->id != id ? NULL : item;
}


/**
 * Remove an item from the slotmap.
 * 
 * @param sm   Pointer to the slot map
 * @param id   Item ID to remove
 */
void sm_remove_item(Slotmap* sm, sm_item_id id)
{
    SMItem* item = sm_get_item(sm, id);
    item->id = (item->id & 0xFFFFFFFF) | (((item->id >> 32) + 1) << 32);
    id = id & 0xFFFFFFFF;
    stack_push(&sm->free_stack, &id);
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
