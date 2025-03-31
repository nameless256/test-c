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

oopFuncPublic(void, setPointSet, uint32_t count, point *set) {
    if (self->set) free(self->set), self->set = NULL;
    self->count = 0;
    if (set) self->set = calloc(count, sizeof(point));
    if (self->set) memcpy(self->set, set, count * sizeof(point)), self->count = count;
}

oopCtor(uint32_t count, point *set) {
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
    memset(self, 0, sizeof(shape));
    shape_setPointSet(self, count, set);
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

oopObjMemAlloc() {
    return oopMemAlloc(sizeof(className));
}

oopObjMemFree() {
    oopMemFree(objPtr);
}
