//
// Created by HASEE on 2024/10/13.
//

#include "private.h"

#define className classDemoBase

mFuncDefine(void, print) {
    if (self) {
        printf("[%d] --------- {%s} name %s age %d\n", __LINE__, __FUNCTION__, self->name, self->age);
    }
}

ctorDefine(const char *name, uint8_t age) {
    if (name) self->name = strdup(name);
    self->age = age;
}

dtorDefine() {
    if (self->name) free(self->name);
}