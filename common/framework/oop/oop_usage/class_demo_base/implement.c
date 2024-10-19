//
// Created by HASEE on 2024/10/13.
//

#include "private.h"

mVarDefine(char *, name)

mVarDefine(uint8_t, age)

mFuncDefine(void, eat) {
    printf("[%d] --------- {%s} Eating... \n", __LINE__, __FUNCTION__);
}

dtorDefine() {
    printf("[%d] --------- {%s} Animal destructor called \n", __LINE__, __FUNCTION__);
}

vFuncTabImplement(className);

ctorDefine() {
    vptrInit();
    vFuncBinding(dtor);
    printf("[%d] --------- {%s} Animal constructor called \n", __LINE__, __FUNCTION__);
}

