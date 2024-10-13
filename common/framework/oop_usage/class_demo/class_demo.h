//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_CLASS_DEMO_H
#define TEST_C_CLASS_DEMO_H

struct classDemo {
    union {
        char _; // 空类占用 1 字节的主要原因是确保每个对象都有一个唯一的地址，并且满足对齐要求。
        struct {

        };
    };
};

#endif //TEST_C_CLASS_DEMO_H
