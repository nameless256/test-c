//
// Created by CodingDev on 2026/2/26.
//
#include "vector_base.h"
#include "util.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void vectorBase_ctor(vectorBase *self, size_t typeSize, size_t capacity, void *value) {
    self->typeSize = typeSize;
    self->size = 0;
    self->data = NULL;
    self->capacity = 0;
    if (typeSize == 0 || capacity == 0) return;
    if (SIZE_MAX / capacity < typeSize) return;
    self->data = malloc(capacity * typeSize);
    if (self->data == NULL) return;
    self->capacity = capacity;
    if (value == NULL) {
        memset(self->data, 0, self->capacity * self->typeSize);
        return;
    }
    fillMemoryWithPattern(self->data, self->typeSize, self->capacity, value);
    self->size = capacity;
}

void vectorBase_dtor(vectorBase *self) {
    self->capacity = 0;
    self->typeSize = 0;
    self->size = 0;
    if (self->data == NULL) return;
    free(self->data);
    self->data = NULL;
}

void *vectorBase_at(vectorBase *self, size_t index) {
    if (index >= self->size) return NULL;
    return self->data + index * self->typeSize;
}

void *vectorBase_front(vectorBase *self) {
    return vectorBase_at(self, 0);
}

void *vectorBase_back(vectorBase *self) {
    return vectorBase_at(self, self->size - 1);
}

void *vectorBase_data(vectorBase *self) {
    return vectorBase_front(self);
}

size_t vectorBase_size(vectorBase *self) {
    return self->size;
}

size_t vectorBase_capacity(vectorBase *self) {
    return self->capacity;
}

bool vectorBase_empty(vectorBase *self) {
    return self->size == 0;
}

void vectorBase_reserve(vectorBase *self, size_t capacity) {
    if (capacity <= self->capacity) return;
    void *reallocPtr = realloc(self->data, capacity * self->typeSize);
    assertReturns(reallocPtr != NULL, "realloc failed");
    self->data = reallocPtr;
    self->capacity = capacity;
}

void vectorBase_set(vectorBase *self, size_t index, void *value) {
    void *ref = vectorBase_at(self, index);
    if (ref == NULL) return;
    memcpy(ref, value, self->typeSize);
}

void vectorBase_pop_back(vectorBase *self) {
    self->size -= 1;
    memset(vectorBase_at(self, self->size), 0, self->typeSize);
}

static void vectorBase_wipe(vectorBase *self, size_t n) {
    while (n != 0) {
        vectorBase_pop_back(self);
        n -= 1;
    }
}

void vectorBase_push_back(vectorBase *self, void *value) {
    if (self->size == self->capacity) {
        vectorBase_reserve(self, self->capacity == 0 ? 1 : 2 * self->capacity);
    }
    memcpy(vectorBase_at(self, self->size), value, self->typeSize);
    self->size += 1;
}

void vectorBase_resize(vectorBase *self, size_t size, void *value) {
    if (size < self->size) {
        size_t less = self->size - size;
        vectorBase_wipe(self, less);
    } else {
        if (size > self->capacity) {
            size_t capacity = 2 * self->size;
            if (size > capacity) capacity = size;
            vectorBase_reserve(self, capacity);
        }
        for (size_t i = 0; self->size < size; i++) {
            vectorBase_push_back(self, value);
        }
    }
}

/// \todo 改成迭代器
void vectorBase_insert(vectorBase *self, size_t index, void *value) {
    if (self->size > 0) {
        vectorBase_push_back(self, vectorBase_back(self));
        memmove(vectorBase_at(self, index + 1), vectorBase_at(self, index), self->typeSize * (self->size - index - 1));
        vectorBase_set(self, index, value);
    } else {
        vectorBase_push_back(self, value);
    }
}

/// \todo 改成迭代器
void vectorBase_erase(vectorBase *self, size_t index) {
    if (index < self->size - 1) {
        memmove(vectorBase_at(self, index), vectorBase_at(self, index + 1), self->typeSize * (self->size - index - 1));
    }
    vectorBase_pop_back(self);
}

void vectorBase_clear(vectorBase *self) {
    if (self->size > 0) {
        vectorBase_wipe(self, self->size);
    }
}

void vectorBase_swap(vectorBase *self, vectorBase *other) {
    vectorBase temp = *self;
    *self = *other;
    *other = temp;
}

void vectorBase_assign(vectorBase* self, size_t size, void *value)
{
    vectorBase_resize(self, size, value);
    for(size_t i = 0; i < size; i++) {
        vectorBase_set(self, i, value);
    }
}
