//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_OOP_H
#define TEST_C_OOP_H

#define public(returnType, className, methodName, ...) returnType className##_##methodName(className *this, ## __VA_ARGS__)

#endif //TEST_C_OOP_H
