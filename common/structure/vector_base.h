//
// Created by CodingDev on 2026/2/26.
//

#ifndef TEST_C_VECTOR_BASE_H
#define TEST_C_VECTOR_BASE_H

#include <stdint.h>
#include <stdbool.h>
#include "mcr_util.h"

typedef struct vectorBase {
    size_t capacity;
    size_t typeSize;
    size_t size;
    void *data;
} vectorBase;

void vectorBase_ctor(vectorBase *self, size_t typeSize, size_t capacity, void *value);
void vectorBase_dtor(vectorBase *self);
void *vectorBase_at(vectorBase *self, size_t index);

#define _vector2(type, name, capacity, value) \
    vectorBase_ctor(&name, sizeof(type), capacity, &(type){value});
#define _vector1(type, name, capacity) \
    vectorBase_ctor(&name, sizeof(type), capacity, 0);
#define _vector0(type, name) \
    vectorBase_ctor(&name, sizeof(type), 0, 0);
#define vector(type, name, ...) \
    vectorBase name __attribute__((cleanup(vectorBase_dtor))); \
    cat2(_vector, mcrVaCount(__VA_ARGS__)) (type, name, ##__VA_ARGS__)

#endif //TEST_C_VECTOR_BASE_H