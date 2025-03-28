//
// Created by HASEE on 2024/10/13.
//

#include "private.h"

mFuncPublic(void, eat) {
    printf("[%d] --------- {%s} Eating... \n", __LINE__, __FUNCTION__);
}

vFuncImpl(void, dtor) {
    printf("[%d] --------- {%s} Animal destructor called \n", __LINE__, __FUNCTION__);
}

dtorDefine() {
    // 需要套层壳进行虚函数调用
    self->vptr->dtor(self);
}

vTab(className);

ctorDefine() {
    vPtrInit();
    vFuncBinding(dtor);
    printf("[%d] --------- {%s} Animal constructor called \n", __LINE__, __FUNCTION__);
}

