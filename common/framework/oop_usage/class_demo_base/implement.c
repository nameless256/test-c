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

ctorDefine(nameAge, const char *name, uint8_t age) {
    if (name) self->name = strdup(name);
    self->age = age;
}

ctorDefine(name, const char *name) {
    ctorCall(nameAge, name, 0);
}

ctorDefine(void) {
    ctorCall(name, "default");
}

dtorDefine() {
    if (self->name) free(self->name);
}