#ifndef SLOTMAP_H
#define SLOTMAP_H

#include <stdio.h>

typedef long long object_id;
const size_t chunk_size = 512;

typedef struct object {
    object_id id;
    double value;
} Object;

#endif
