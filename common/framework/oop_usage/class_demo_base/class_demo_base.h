//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_CLASS_DEMO_BASE_H
#define TEST_C_CLASS_DEMO_BASE_H

#include "tool.h"
#include <stdlib.h>
#include <stdio.h>

struct classDemoBase {
    union {
        char _; // 空类占用 1 字节的主要原因是确保每个对象都有一个唯一的地址，并且满足对齐要求。
        struct {
            char *name;
            uint8_t age;
        };
    };
};

void classDemoBase_print(struct classDemoBase *self) {
    if (self) {
        printf("[%d] --------- {%s} name %s age %d\n", __LINE__, __FUNCTION__, self->name, self->age);
    }
}

void classDemoBase_ctor_43(struct classDemoBase *self, const char *name, uint8_t age) {
    if (name) self->name = strdup(name);
    self->age = age;
}

void classDemoBase_ctor_36(struct classDemoBase *self, const char *name) {
    uint8_t age = 0;
    classDemoBase_ctor_43(self, name, age);
}

void classDemoBase_ctor_28(struct classDemoBase *self) {
    const char *name = "default";
    classDemoBase_ctor_36(self, name);
}

struct classDemoBase *new_classDemoBase(const char *name, uint8_t age) {
    struct classDemoBase *self = calloc(1, sizeof(struct classDemoBase));
    if (self) classDemoBase_ctor_43(self, name, age);
    return self;
}

void classDemoBase_dtor(struct classDemoBase *self) {
    if (self->name) free(self->name);
}

void delete_classDemoBase(struct classDemoBase *self) {
    if (!self) return;
    classDemoBase_dtor(self);
    free(self);
}

#endif //TEST_C_CLASS_DEMO_BASE_H
