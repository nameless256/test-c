//
// Created by CodingDev on 2026/2/26.
//

#define VECTOR_BASE_H_IMPL
#include "vector_base.h"
#include "obj.h"

#include <malloc.h>
#include <stdio.h>

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
#if 1
    if (idx < 0) idx = self->size + idx;
    if (idx < 0 || idx >= self->size) return NULL;
#else
    if (self->size == 0) return NULL;
    idx %= self->size;
    if (idx < 0) idx += self->size;
#endif
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

method(void *, data) {
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

method(bool, addTail, bool isClass, size_t elmSize, void *elm) {
    if (self->size >= self->capacity) {
        if (reserve(self, 1, elmSize)) return true;
    }
    void *dst = self->data + self->size * elmSize;
    if (isClass) obj_copy(dst, elm);
    else memcpy(dst, elm, elmSize);
    self->size++;
    return false;
}

method(void *, delTail, bool isClass, size_t elmSize) {
    void *elm = tail(self, elmSize);
    if (self->size) self->size--;
    if (elm == NULL) return NULL;
    if (isClass) obj_dtor(elm);
    else memset(elm, 0, elmSize);
    return elm;
}
