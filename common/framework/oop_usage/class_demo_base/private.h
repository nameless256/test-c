//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_PRIVATE_H
#define TEST_C_PRIVATE_H

#include "protected.h"

// 所有数据均为私有 仅允许通过getter和setter访问
classDef(classDemoBase)
            char *name;
            uint8_t age;
classDefEnd

#endif //TEST_C_PRIVATE_H
