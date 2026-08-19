//
// Created by CodingDev on 2026/2/26.
//

#define VECTOR_BASE_H_IMPL
#include "vector_base.h"
#include "obj.h"

#include <malloc.h>
#include <stdio.h>

#define className vectorBase

method(bool, copy, className *other) {
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

method(void *, at, size_t elmSize, int idx) {
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

method(bool, reserve, size_t elmSize, size_t capacity) {
    if (capacity == self->capacity) return false;
    size_t ex = self->capacity + (self->capacity >> 1);
    if (ex < capacity) ex = capacity;
    if (alloc_safe(&self->data, elmSize * ex, 0)) return false;
    self->capacity = ex;
    return true;
}

method(void *, end, size_t elmSize) {
    return self->data + self->size * elmSize;
}

method(bool, addTail, size_t elmSize, void *elm) {
    if (self->size >= self->capacity) {
        if (reserve(self, 1, elmSize)) return true;
    }
    void *dst = end(self, elmSize);
    memcpy(dst, elm, elmSize);
    self->size++;
    return false;
}

method(void, delTail, size_t elmSize) {
    void *elm = tail(self, elmSize);
    if (elm == NULL) return;
    self->size--;
    memset(elm, 0, elmSize);
}

method(bool, add, size_t elmSize, int idx, size_t count, void *elm) {
    if (self->size >= self->capacity) {
        if (reserve(self, 1, elmSize)) return true;
    }
    void *dst = at(self, elmSize, idx);
    if (dst == NULL) return true;
    size_t moveSize = end(self, elmSize) - dst;
    if (count == 0) count = 1;
    memmove(dst + elmSize * count, dst, moveSize);
    memFill(dst, elm, elmSize, count);
    self->size += count;
    return false;
}

method(void, del, size_t elmSize, int idx, size_t count) {
    void *elm = at(self, elmSize, idx);
    if (elm == NULL) return;
    if (count == 0) count = 1;
    size_t delSize = elmSize * count;
    if (end(self, elmSize) - elm < delSize) {
        delSize = end(self, elmSize) - elm;
    } else {
        void *src = elm + delSize;
        size_t moveSize = end(self, elmSize) - src;
        memmove(elm, src, moveSize);
    }
    self->size -= (delSize / elmSize);
    memset(end(self, elmSize) - delSize, 0, delSize);
}

method(void, clear, size_t elmSize) {
    if (self->size == 0) return;
    size_t delSize = elmSize * self->size;
    self->size = 0;
    memset(self->data, 0, delSize);
}

method(bool, resize, size_t elmSize, void *elm, size_t count) {
    if (count < self->size) {
        count = self->size - count;
        for (int i = 0; i < count; ++i) {
            delTail(self, elmSize);
        }
    } else if (count > self->size) {
        count = count - self->size;
        for (int i = 0; i < count; ++i) {
            if (addTail(self, elmSize, elm)) return true;
        }
    }
    return false;
}

method(void, swap, className *other) {
    className temp = *other;
    *other = *self;
    *self = temp;
}

