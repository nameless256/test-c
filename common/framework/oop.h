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

/**
 * @attention 由于 继承 的特性
 * @attention 无法在 C语言 中实现 成员变量 的 访问控制
 * @attention 所有 派生类 中定义的 成员变量 仅允许 派生类 的 成员函数 直接访问
 * @attention 成员函数 访问权限 由 声明文件 决定
 * @attention 派生类 访问 基类 的 成员变量 仅允许 通过 基类 的 成员函数 间接访问
 */

/**
 * @details 空类的对象占用 1 字节的原因是为了保证每个对象在内存中有唯一的地址。
 * @details 这是 C++ 标准的规定，以确保即使对于空类，不同对象的指针也可以区分。
 * @details 空的结构体（struct）在 C++ 中也是同样的处理方式，即占用 1 字节。
 * @details 这是因为 struct 和 class 在 C++ 中除了默认访问控制外，其他方面几乎相同。
 * @details 这种设计有助于避免多个空对象实例共享同一个地址，从而简化了指针和引用的管理，特别是在多态和继承的情况下。
 */
#define classDef(className, ...) \
struct className; \
typedef struct className className; \
struct className { \
    union { \
        char _; \
        struct { \
            __VA_ARGS__ __VA_ARGS__;

#define classDefEnd \
        }; \
    }; \
};

#define cThis ((className *)self)

/******************************************************************/ // [ 虚函数 ] 的 声明 及 定义

#define vFuncTabDef struct CONCAT3(className, _, vFuncTab) {

#define vFuncTabDefEnd } const *vptr;

#define vFuncTabImplement \
static struct CONCAT3(className, _, vFuncTab) CONCAT3(className, _, vFuncTab) = {}

#define vFuncTabBaseImplement \
static struct CONCAT3(classBaseName, _, vFuncTab) CONCAT3(classBaseName, _, vFuncTab) = {}

#define vFuncDeclare(returnType, methodName, ...) \
returnType (*methodName)(void *self, ## __VA_ARGS__)

#define vFuncOverride(methodName) \
CONCAT3(classBaseName, _, vFuncTab).methodName = CONCAT3(className, _, methodName)

#define vFuncBinding(methodName) \
CONCAT3(className, _, vFuncTab).methodName = CONCAT3(className, _, methodName)

#define vptrInit() cThis->vptr = &CONCAT3(className, _, vFuncTab)

#define vptrBaseInit() \
CONCAT3(classBaseName, _, vFuncTab) = *cThis->classBaseName.vptr; \
cThis->classBaseName.vptr = &CONCAT3(classBaseName, _, vFuncTab)

#define vCtorDeclare(...) \
void (*ctor)(void *self, ## __VA_ARGS__)

#define vDtorDeclare() \
void (*dtor)(void *self)

/******************************************************************/ // [ 成员函数 ] 的 声明 及 定义

#define mFuncAddr(methodName) CONCAT3(className, _, methodName)

#define mFuncCall(methodName, ...) mFuncAddr(methodName)(self, ## __VA_ARGS__)

#define mFuncBaseAddr(methodName) CONCAT3(classBaseName, _, methodName)

#define mFuncBaseCall(methodName, ...) mFuncBaseAddr(methodName)(self, ## __VA_ARGS__)

#define mFuncDeclare(returnType, methodName, ...) \
returnType mFuncAddr(methodName)(void *self, ## __VA_ARGS__)

#define mFuncDefine(returnType, methodName, ...) \
mFuncDeclare(returnType, methodName, ## __VA_ARGS__)

/******************************************************************/ // [ 成员变量 访问器 ] 的 声明 及 定义

#define mVarDeclare(type, varName) \
type CONCAT3(className, _get_, varName)(void *self); \
void CONCAT3(className, _set_, varName)(void *self, type val)

#define mVarDefine(type, varName) \
type CONCAT3(className, _get_, varName)(void *self) { return cThis->varName; } \
void CONCAT3(className, _set_, varName)(void *self, type val) { cThis->varName = val; }

/******************************************************************/ // [ 构造 / 析构 ] 的 声明 及 定义

#define ctorDeclare(...) \
void CONCAT(className, _ctor)(void *self, ## __VA_ARGS__)

#define ctorDefine(...) \
ctorDeclare(__VA_ARGS__)

#define ctorAddr() CONCAT(className, _ctor)

#define ctorCall(methodName, ...) ctorAddr()(self, ## __VA_ARGS__)

#define ctorBaseAddr() CONCAT(classBaseName, _ctor)

#define ctorBaseCall(...) ctorBaseAddr()(self, ## __VA_ARGS__)

#define dtorDeclare() \
void CONCAT(className, _dtor)(void *self)

#define dtorDefine() \
dtorDeclare()

#define dtorBaseAddr() CONCAT(classBaseName, _dtor)

#define dtorBaseCall() dtorBaseAddr()(self)

/******************************************************************/ // 在栈上 [ 创建 / 销毁 ] 对象

/// 难以支持重载, 真要做只能建议在 构造函数 内 通过 self 后面的第一个参数再套一层可变参数
#define obj_create(className, varName, ...) \
    className varName; \
    CONCAT3(className, _, ctor)(&varName, ## __VA_ARGS__)

/// 无法在退出作用域时自动销毁对象 (需要手动调用)
#define obj_destroy(className, varName) \
    CONCAT3(className, _, dtor)(&varName)

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define obj_new(className, varName, ...) \
    className *varName = calloc(1, sizeof(struct className)); \
    if (varName) CONCAT3(className, _ctor)(varName, ## __VA_ARGS__)

#define obj_delete(className, varName) \
    if (varName) {CONCAT3(className, _dtor)(varName); free(varName);}

#endif //TEST_C_OOP_H
