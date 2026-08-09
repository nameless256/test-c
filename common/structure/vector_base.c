//
// Created by CodingDev on 2026/2/26.
//

#define VECTOR_BASE_H_IMPL
#include "vector_base.h"
#include <malloc.h>

#include "stdio.h"

#define className vector_base

method(bool, ctor) {
    printf("0xOil: %-4d{%s} \n", __LINE__, __FUNCTION__);
    return false;
}

method(bool, copy, vector_base *other) {
    *self = *other;
    return false;
}

method(void, dtor) {
    if (self->data == NULL) return;
    free(self->data);
    self->data = NULL;
}

method(size_t, capacity) {
    return self->capacity;
}

method(size_t, size) {
    return self->size;
}

method(bool, empty) {
    return self->size == 0;
}

method(void *, at, int idx, size_t elmSize) {
    if (self->size == 0) return NULL;
    if (idx < 0) {
        idx = -idx;
        idx %= self->size;
        idx = self->size - idx;
    }
    if (idx >= self->size) idx %= self->size;
    return self->data + idx * elmSize;
}

method(void *, tail, size_t elmSize) {
    if (self->size == 0) return NULL;
    return self->data + (self->size - 1) * elmSize;
}

method(void *, head) {
    if (self->size == 0) return NULL;
    return self->data;
}

method(bool, reserve, size_t capacity, size_t elmSize) {
    if (capacity == self->capacity) return false;
    size_t ex = self->capacity + (self->capacity >> 1);
    if (ex < capacity) ex = capacity;
    if (alloc_safe(&self->data, elmSize * ex, 0)) return false;
    self->capacity = ex;
    return true;
}
