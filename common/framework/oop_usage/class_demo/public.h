//
// Created by xiaoxianghui on 2024/10/16.
//

#ifndef TEST_C_CLASS_DEMO_PUBLIC_H
#define TEST_C_CLASS_DEMO_PUBLIC_H

#include "oop.h"
#include "tool.h"
#include <stdlib.h>
#include <stdio.h>

// 公共 继承 include *\public
#include "class_demo_base/public.h"

#undef classBaseName
#define classBaseName Animal

// 派生类类名 定义
#undef className
#define className Dog

classDef(className, classBaseName)
classDefEnd

mFuncDeclare(void, displayInfo);

ctorDeclare();

dtorDeclare();

#endif //TEST_C_CLASS_DEMO_PUBLIC_H
