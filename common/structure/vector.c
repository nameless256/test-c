//
// Created by CodingDev on 2026/2/26.
//

#define VECTOR_H_IMPL
#include "vector.h"
#include <malloc.h>

#include "stdio.h"

#define MODULE vector_base

#define $decl(ret, func, ...) \
ret cat_2(MODULE, func)(__VA_ARGS__)

#define public(ret, func, ...) \
ret func(__VA_ARGS__) __attribute__((alias(nameVal2Str(cat_2(MODULE, func))))); \
ret cat_2(MODULE, func)(__VA_ARGS__)

public(bool, ctor, objBase *obj) {
    printf("0xOil: %-4d{%s} \n", __LINE__, __FUNCTION__);
    return false;
}

//$(copy, objBase *obj, objBase *src) {
bool vector_base_copy(objBase *dst, objBase *src) {
    printf("0xOil: %-4d{%s} \n", __LINE__, __FUNCTION__);
    return ctor(NULL);
}

void vector_base_dtor(objBase *obj) {
    vector_base *self = (vector_base *) obj;
    if (self->data == NULL) return;
    free(self->data);
    self->data = NULL;
}

public(void, test, vector_base *self, int i) {
//void vector_base_test(vector_base *self) {
    printf("0xOil: %-4d{%s} \n", __LINE__, __FUNCTION__);
}

// #include "vector_base.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

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
