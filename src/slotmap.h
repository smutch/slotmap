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

#ifndef SLOTMAP_H
#define SLOTMAP_H

#include <stdio.h>
#include "stack.h"

/** The size to grow the slot map by each time it grows. */
#define SM_CHUNK_SIZE 512

typedef long long sm_item_id;

typedef struct item {
    sm_item_id id;
    double value;
} SMItem;

typedef struct slotmap {
    Stack free_stack;
    Stack chunk_stack; 
} Slotmap;

Slotmap sm_new(void);
SMItem* sm_create_item(Slotmap* sm);
SMItem* sm_get_item(Slotmap* sm, sm_item_id id);
void sm_remove_item(Slotmap* sm, sm_item_id id);
void sm_destroy(Slotmap* sm);

#endif
