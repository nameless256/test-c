//
// Created by CodingDev on 2026/7/21.
//

#ifndef TEST_C_OBJ_H
#define TEST_C_OBJ_H

#include "meta.h"

void obj_dtor(void *obj);
bool obj_ctor(void *obj);
bool obj_copy(void *restrict dst, void *restrict src);

#endif //TEST_C_OBJ_H
