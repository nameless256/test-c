//
// Created by CodingDev on 2026/2/26.
//
#include "vector_base.h"
#include "util.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "vector.h"

void vector_dtor(void *v) {
    if (v) free(vector_getMeta(v));
}

void vector_cleanup(void *p2p) {
    void *self = *((void **) p2p);
    vector_dtor(self);
}

void vector_reserve(void *v, size_t c) {
    if (c == vector_capacity(v)) return;
    size_t ex = vector_capacity(v) + (vector_capacity(v) >> 1);
    if (ex < c) ex = c;
    /// \todo alloc_safe return true 时异常抛出
    if (alloc_safe((void **) &v, vector_getMeta(v)->typeSize * ex, sizeof(vectorMeta))) return;
    vector_capacity(v) = ex;
}
