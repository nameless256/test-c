//
// Created by CodingDev on 2026/7/21.
//

#ifndef TEST_C_OBJ_H
#define TEST_C_OBJ_H

#include "meta.h"

#define _accessDispatch00(f0, f1, ...) f1(__VA_ARGS__)
#define _accessDispatch01(f0, f1, ...) f1(__VA_ARGS__)
#define _accessDispatch02(f0, f1, ...) f1(__VA_ARGS__)
#define _accessDispatch10(f0, f1, ...) f0(__VA_ARGS__)
#define _accessDispatch11(f0, f1, ...) f1(__VA_ARGS__)
#define _accessDispatch12(f0, f1, ...) f1(__VA_ARGS__)
#define _accessDispatch20(f0, f1, ...) f0(__VA_ARGS__)
#define _accessDispatch21(f0, f1, ...) f0(__VA_ARGS__)
#define _accessDispatch22(f0, f1, ...) f1(__VA_ARGS__)
#define accessDispatch(f0, f1, ...) cat3(_accessDispatch, accessLv, accessCtrl)(f0, f1, ##__VA_ARGS__)

#define _dummyVoid(...)

#define _dummyVirtual(ret, func, ...) void *func

#define _export(ret, func, ...) \
ret cat_2(className, func)(className *self, ##__VA_ARGS__)

#define _virtual(ret, func, ...) ret (*func)(className *self, ##__VA_ARGS__)

#define _bind(name) .name = name

#define method(ret, func, ...) \
ALIAS(func) _export(ret, func, ##__VA_ARGS__); \
static ret func(className *self, ##__VA_ARGS__)

#define $protected  1
#define $private    2
#define $public     0

#define classVtabStart static const cat_2(className, vtab) vtab = {

#define classVtabEnd };

#define classVtabDefStart \
typedef struct cat_2(className, vtab) cat_2(className, vtab); \
struct cat_2(className, vtab) { \
    _virtual(bool, ctor); \
    _virtual(void, dtor); \
    _virtual(bool, copy, className *other);

#define classVtabDefEnd };

#define $(self, func, ...) (self)->vtab->func(self, ##__VA_ARGS__)

void obj_dtor(void *obj);
bool obj_ctor(void *obj);
bool obj_copy(void *restrict dst, void *restrict src);

#endif //TEST_C_OBJ_H
