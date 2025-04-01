//
// Created by xiaoxianghui on 2025/3/31.
//

#include <stdlib.h>
#include <stdio.h>
#include "rect.h"

#define classBaseName shape

oopClassDefine() {
    oopInherit();
    point pos;
    uint32_t w, h;
};

oopCreate(point pos, uint32_t w, uint32_t h) {
    className *self = oopMemAlloc(sizeof(className));
    oopObjCreate(classBaseName, self->base)(0, NULL);
    self->base = shape_create(0, NULL);
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
    point set[] = {pos, {pos.x + w, pos.y}, {pos.x + w, pos.y + h}, {pos.x, pos.y + h}};
    shape_setPointSet(self->base, 4, set);
    self->pos = pos;
    self->w = w, self->h = h;
    return self;
}

oopDestroy() {
    oopObjDestroy(classBaseName, self->base);
    printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
    oopMemFree(self);
}

oopFuncPublic(void, print) {
    printf("[%d] --------- {%s} pos (%d, %d) w %d h %d\n", __LINE__, __FUNCTION__,
           self->pos.x, self->pos.y, self->w, self->h);
    shape_print(self->base);
}
