//
// Created by CodingDev on 2026/2/26.
//

#include <malloc.h>
#include <string.h>

#include "vector_base.h"
#include <stdio.h>

void vectorBase_ctor(vectorBase *self, size_t size, size_t capacity, void *initialize) {
    self->size = size;
    self->length = 0;
    self->data = NULL;
    if (size == 0 || capacity == 0) return;
    if (SIZE_MAX / capacity < size) return;
    self->data = malloc(capacity * size);
    if (self->data == NULL) return;
    self->capacity = capacity;
    if (initialize == NULL) {
        memset(self->data, 0, self->capacity * self->size);
        return;
    }
    char *dest = (char *) self->data;
    const char *src = (const char *) initialize;
    memcpy(dest, src, self->size);
    if (self->capacity > 1) {
        size_t offset = self->size;
        size_t remaining = (self->capacity - 1) * self->size;
        while (remaining > 0) {
            size_t copy_size = (offset < remaining) ? offset : remaining;
            memmove(dest + offset, dest, copy_size);
            offset += copy_size;
            remaining -= copy_size;
        }
    }
}

void vectorBase_dtor(vectorBase *self) {
    self->size = 0;
    self->length = 0;
    self->capacity = 0;
    free(self->data);
    self->data = NULL;
}

void *vectorBase_at(vectorBase *self, size_t index) {
    return self->data + index * self->size;
}
