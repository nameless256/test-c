//
// Created by xiaoxianghui on 2024/10/16.
//

#ifndef TEST_C_PUBLIC_H
#define TEST_C_PUBLIC_H

#include "oop.h"
#include "tool.h"
#include <stdlib.h>
#include <stdio.h>

classDeclare(classDemoBase);

mFuncDeclare(void, classDemoBase, print);

ctorDeclare(classDemoBase, nameAge, const char *name, uint8_t age);

ctorDeclare(classDemoBase, name, const char *name);

ctorDeclare(classDemoBase, void);

dtorDeclare(classDemoBase);

#endif //TEST_C_PUBLIC_H
