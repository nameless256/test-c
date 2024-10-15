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

// 空类占用 1 字节的主要原因是确保每个对象都有一个唯一的地址，并且满足对齐要求。
#define classDef(className) \
struct className { \
    union { \
        char _; \
        struct {
//            ITERATE_ROOTS(DEFINE_ROOT)

#define classDefEnd \
        }; \
    }; \
};

#define public(returnType, className, methodName, ...) returnType className##_##methodName(className *this, ## __VA_ARGS__)

#endif //TEST_C_OOP_H
