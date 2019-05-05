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
 * @returns The new slot map initialized with an item table of size
 *          :macro:`SM_CHUNK_SIZE`.
 */
Slotmap sm_new()
{
    Slotmap sm;
    sm.free_stack = stack_new(sizeof(sm_item_id), SM_CHUNK_SIZE);
    sm.item_table = calloc(SM_CHUNK_SIZE, sizeof(SMItem));

    if (sm.item_table == NULL)
        fprintf(stderr, "Failed to malloc slotmap item table!\n");

    return sm;
}


sm_item_id sm_create_object()
{
    return EXIT_SUCCESS;
}

SMItem* sm_get_object()
{
    return NULL;
}


/**
 * Destroy the slot map and free associated memory.
 * 
 * @param sm   Pointer to the slot map
 */
void sm_destroy(Slotmap* sm)
{
    stack_destroy(&sm->free_stack);
    free(sm->item_table);
    sm->item_table = NULL;
}
