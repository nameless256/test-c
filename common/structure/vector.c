//
// Created by CodingDev on 2026/2/26.
//

#include <stdlib.h>

#include "vector_base.h"

void vectorBase_ctor(vectorBase *self, size_t size, size_t capacity) {
    self->data = malloc(self->capacity * self->size);
    self->capacity = capacity;
    self->size = size;
    self->length = 0;
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




