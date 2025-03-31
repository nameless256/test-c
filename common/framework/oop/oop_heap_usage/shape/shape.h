//
// Created by xiaoxianghui on 2025/3/29.
//

#ifndef TEST_C_SHAPE_H
#define TEST_C_SHAPE_H

#include "oop.h"
#include <stdint.h>

typedef struct {
    uint32_t x, y;
} point;

#define className Shape

oopClassDeclare()

oopCtor(uint32_t count, point *set);

oopDtor();

oopFuncPublic(void, print);

#endif //TEST_C_SHAPE_H
