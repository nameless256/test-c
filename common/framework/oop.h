//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_OOP_H
#define TEST_C_OOP_H

#define LV_IMG_CACHE_DEF 1

#define _CONCAT(x, y) x ## y
#define CONCAT(x, y) _CONCAT(x, y)

#define _CONCAT3(x, y, z) x ## y ## z
#define CONCAT3(x, y, z) _CONCAT3(x, y, z)

#define _CONCAT4(a, b, c, d) a ## b ## c ## d
#define CONCAT4(a, b, c, d) _CONCAT3(a, b, c, d)

#define LV_DISPATCH(f, t, n)            f(t, n)
#define LV_DISPATCH_COND(f, t, n, m, v) CONCAT3(LV_DISPATCH, m, v)(f, t, n)

#define LV_DISPATCH00(f, t, n)          LV_DISPATCH(f, t, n)
#define LV_DISPATCH01(f, t, n)
#define LV_DISPATCH10(f, t, n)
#define LV_DISPATCH11(f, t, n)          LV_DISPATCH(f, t, n)

#define ITERATE_ROOTS(f)                                                                            \
    LV_DISPATCH(f, int, _lv_timer_ll) /*Linked list to store the lv_timers*/                       \
    LV_DISPATCH_COND(f, int*, _lv_img_cache_array, LV_IMG_CACHE_DEF, 1)              \

#define DEFINE_ROOT(root_type, root_name) root_type root_name;

#include <stdarg.h>

#define classDeclare(className) \
struct className; \
typedef struct className className

// 空类占用 1 字节的主要原因是确保每个对象都有一个唯一的地址，并且满足对齐要求。
#define classDef(className) \
struct className { \
    union { \
        char _; \
        struct {

#define classDefEnd \
        }; \
    }; \
};

#define mFuncDeclare(returnType, className, methodName, ...) \
returnType CONCAT3(className, _, methodName)(className *self, ## __VA_ARGS__)

#define mFuncDefine(returnType, methodName, ...) \
mFuncDeclare(returnType, className, methodName, ## __VA_ARGS__)

#define mVarDeclare(className, type, varName) \
type CONCAT3(className, _get_, varName)(className *self); \
void CONCAT3(className, _set_, varName)(className *self, type val)

#define mVarDefine(type, varName) \
type CONCAT3(className, _get_, varName)(className *self) { return self->varName; } \
void CONCAT3(className, _set_, varName)(className *self, type val) { self->varName = val; }

#define ctorDeclare(className, ctorName, ...) \
void CONCAT3(className, _ctor_, ctorName)(className *self, ## __VA_ARGS__)

#define ctorDefine(ctorName, ...) \
void CONCAT3(className, _ctor_, ctorName)(className *self, ## __VA_ARGS__)

#define dtorDeclare(className) \
void CONCAT(className, _dtor)(className *self); \
void CONCAT(delete_, className)(className *self)

#define dtorDefine() \
void CONCAT(delete_, className)(className *self) { \
    if (!self) return; \
    CONCAT(className, _dtor)(self); \
    free(self); \
} \
void CONCAT(className, _dtor)(className *self)

#define ctorCall(ctorName, ...) CONCAT3(className, _ctor_, ctorName)(self, ## __VA_ARGS__)

#define new_obj(className, varName, ctor, ...) \
    className *varName = calloc(1, sizeof(struct classDemoBase)); \
    if (varName) ctor(varName, ## __VA_ARGS__);

#define delete_obj(className, variableName) \
    CONCAT(className, _dtor)(variableName, ## __VA_ARGS__); \
    free(variableName);

#endif //TEST_C_OOP_H
