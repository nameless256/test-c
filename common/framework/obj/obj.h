//
// Created by CodingDev on 2026/7/21.
//

#ifndef TEST_C_OBJ_H
#define TEST_C_OBJ_H

#include "meta.h"

void obj_dtor(objBase *obj);
bool obj_ctor(objBase *obj);
bool obj_copy(objBase *restrict obj, objBase *restrict other);

#endif //TEST_C_OBJ_H
