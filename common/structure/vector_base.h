//
// Created by CodingDev on 2026/2/26.
//

#ifndef TEST_C_VECTOR_BASE_H
#define TEST_C_VECTOR_BASE_H

#include <stdint.h>

typedef struct vectorBase {
    size_t capacity;
    size_t length;
    size_t size;
    void *data;
} vectorBase;

void vectorBase_ctor(vectorBase *self, size_t size, size_t capacity);
void vectorBase_dtor(vectorBase *self);
void *vectorBase_at(vectorBase *self, size_t index);

#endif //TEST_C_VECTOR_BASE_H