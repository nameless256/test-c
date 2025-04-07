//
// Created by HASEE on 2024/10/13.
//

#include "private.h"

oopPublic(void, eat) {
    printf("[%d] --------- {%s} Eating... \n", __LINE__, __FUNCTION__);
}

oopVFuncImpl(void, dtor) {
    printf("[%d] --------- {%s} Animal destructor called \n", __LINE__, __FUNCTION__);
}

oopDtor() {
    // 需要套层壳进行虚函数调用
    self->vptr->dtor(self);
}

oopVTab(className);

oopCtor() {
    oopVPtrInit();
    oopVFuncBinding(dtor);
    printf("[%d] --------- {%s} Animal constructor called \n", __LINE__, __FUNCTION__);
}

