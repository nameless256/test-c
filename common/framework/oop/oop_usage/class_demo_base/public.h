//
// Created by xiaoxianghui on 2024/10/16.
//

#ifndef TEST_C_PUBLIC_H
#define TEST_C_PUBLIC_H

#include "oop.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

// 公共 继承 include *\public

// 基类
#undef classBaseName
#define classBaseName

// 派生类类名 定义
#undef className
#define className animal

oopClassDef
            oopVPtrDef
                oopVFuncDeclare(void, makeSound);
                oopVDtorDeclare();
            oopVPtrDefEnd
            char *name;
            uint8_t age;
oopClassDefEnd

oopFuncPublic(void, eat);

oopCtor();

oopDtor();

oopObjMemAlloc();

oopObjMemFree();

#endif //TEST_C_PUBLIC_H
