//
// Created by HASEE on 2024/9/22.
//

#ifndef TEST_C_CLASS_T_H
#define TEST_C_CLASS_T_H

#include <stdint.h>

typedef struct class_t {
    struct class_t *base;
    void (*ctor)(struct class_t *self);
    void (*ctorCopy)(struct class_t *self, struct class_t *src);
    void (*dtor)(struct class_t *self);
    uint32_t attribute;
    void *private;
} *class_t;

#endif //TEST_C_CLASS_T_H
