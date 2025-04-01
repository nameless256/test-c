//
// Created by xiaoxianghui on 2025/3/31.
//

#ifndef TEST_C_RECT_H
#define TEST_C_RECT_H

#include "oop.h"
#include <stdint.h>
#include "shape/shape.h"

#undef className
#define className rect

oopClassDeclare()

oopCreate(point pos, uint32_t w, uint32_t h);

oopDestroy();

oopFuncPublic(void, print);

#endif //TEST_C_RECT_H
