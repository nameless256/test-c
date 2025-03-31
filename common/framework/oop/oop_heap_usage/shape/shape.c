//
// Created by xiaoxianghui on 2025/3/29.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shape.h"

oopClassDefine() {
    uint32_t count;
    point *set;
};

oopCtor(uint32_t count, point *set) {
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
    self->set = calloc(count, sizeof(point));
    self->count = count;
    if (!self->set) self->count = 0;
    else memcpy(self->set, set, count * sizeof(point));
}

oopDtor(){
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
}

oopFuncPublic(void, print) {
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
    for (uint32_t i = 0; i < self->count; ++i) {
        printf("(%d, %d)", self->set[i].x, self->set[i].y);
        printf(i < self->count - 1 ? ", " : "\n");
    }
}
