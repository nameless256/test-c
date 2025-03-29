//
// Created by HASEE on 2024/10/13.
//

#include "private.h"

vFuncImpl(void, makeSound) {
    printf("[%d] --------- {%s} Barking... \n", __LINE__, __FUNCTION__);
}

mFuncPublic(void, displayInfo) {
    // 虽然说可以这么做, 但不推荐, 本质上是绕过了封装, 导致原有的访问控制的方法失效了
//    printf("[%d] --------- {%s} Name: %s \n", __LINE__, __FUNCTION__, ((classBaseName *) self)->name);
    printf("[%d] --------- {%s} Name: %s \n", __LINE__, __FUNCTION__, animal_get_name(&self->animal));
}

dtorDefine() {
    dtorBaseCall();
    printf("[%d] --------- {%s} Dog destructor called \n", __LINE__, __FUNCTION__);
}

vTab(classBaseName);

ctorDefine() {
    ctorBaseCall();
    vPtrBaseInit();
    vFuncOverride(makeSound);
    printf("[%d] --------- {%s} Dog constructor called \n", __LINE__, __FUNCTION__);
    animal_set_name(&self->animal, "Rex");
}
