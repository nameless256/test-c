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

classDef
            vPtrDef
                vFuncDeclare(void, makeSound);
                vDtorDeclare();
            vPtrDefEnd
            char *name;
            uint8_t age;
classDefEnd

mFuncPublic(void, eat);

ctorDeclare();

dtorDeclare();

#endif //TEST_C_PUBLIC_H
