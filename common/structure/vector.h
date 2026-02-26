//
// Created by CodingDev on 2026/2/26.
//

#include "mcr_util.h"
#include <stdint.h>

#define T int
#ifndef T
#error "T is not defined"
#endif
#define VEC_T cat_2(vector, T)

typedef struct VEC_T VEC_T;
struct VEC_T {
    /// 通过函数指针结构体调用类型擦除的容器接口

    T (*at)(VEC_T *self, size_t index);
};

#undef T
#undef VEC_T
