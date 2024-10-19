//
// Created by HASEE on 2024/10/13.
//

#ifndef TEST_C_OOP_H
#define TEST_C_OOP_H

#define _CONCAT3(x, y, z) x ## y ## z
#define CONCAT3(x, y, z) _CONCAT3(x, y, z)

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

/******************************************************************/ // [ 成员函数 ] 的 声明 及 定义

#define mFuncName(methodName) CONCAT3(className, _, methodName)
#define mFuncCall(methodName, ...) mFuncName(methodName)(self, ## __VA_ARGS__)

#define mFuncBaseName(methodName) CONCAT3(classBaseName, _, methodName)
#define mFuncBaseCall(methodName, ...) mFuncBaseName(methodName)(self, ## __VA_ARGS__)

#define mFuncDeclare(returnType, methodName, ...) returnType mFuncName(methodName)(void *self, ## __VA_ARGS__)
#define mFuncDefine(returnType, methodName, ...) mFuncDeclare(returnType, methodName, ## __VA_ARGS__)

/******************************************************************/ // [ 虚函数 ] 的 声明 及 定义

#define vFuncTabName(className) CONCAT3(className, _, vFuncTab)

#define vFuncTabDef struct vFuncTabName(className) {

#define vFuncTabDefEnd } const *vptr;

#define vFuncTabImplement(className) \
static struct vFuncTabName(className) vFuncTabName(className) = {}

#define vFuncDeclare(returnType, methodName, ...) \
returnType (*methodName)(void *self, ## __VA_ARGS__)

#define vptrInit() \
    cThis->vptr = &vFuncTabName(className)

#define vFuncBinding(methodName) \
    vFuncTabName(className).methodName = mFuncName(methodName)

#define vptrBaseInit() \
    vFuncTabName(classBaseName) = *cThis->classBaseName.vptr; \
    cThis->classBaseName.vptr = &vFuncTabName(classBaseName)

#define vFuncOverride(methodName) \
    vFuncTabName(classBaseName).methodName = mFuncName(methodName)

#define vCtorDeclare(...) void (*ctor)(void *self, ## __VA_ARGS__)
#define vDtorDeclare() void (*dtor)(void *self)

/******************************************************************/ // [ 成员变量 访问器 ] 的 声明 及 定义

#define mVarDeclare(type, varName) \
type CONCAT3(className, _get_, varName)(void *self); \
void CONCAT3(className, _set_, varName)(void *self, type val)

#define mVarDefine(type, varName) \
type CONCAT3(className, _get_, varName)(void *self) { return cThis->varName; } \
void CONCAT3(className, _set_, varName)(void *self, type val) { cThis->varName = val; }

/******************************************************************/ // [ 构造 / 析构 ] 的 声明 及 定义

#define ctorName mFuncName(ctor)
#define ctorDeclare(...) void ctorName(void *self, ## __VA_ARGS__)
#define ctorDefine(...) ctorDeclare(__VA_ARGS__)
#define ctorCall(methodName, ...) ctorName(self, ## __VA_ARGS__)

#define ctorBaseName CONCAT3(classBaseName, _, ctor)
#define ctorBaseCall(...) ctorBaseName(self, ## __VA_ARGS__)

#define dtorName mFuncName(dtor)
#define dtorDeclare() void dtorName(void *self)
#define dtorDefine() dtorDeclare()
#define dtorCall(methodName) dtorName(self)

#define dtorBaseName CONCAT3(classBaseName, _, dtor)
#define dtorBaseCall() dtorBaseName(self)

/******************************************************************/ // 在栈上 [ 创建 / 销毁 ] 对象

/// 难以支持重载, 真要做只能建议在 构造函数 内 通过 self 后面的第一个参数再套一层可变参数
#define obj_create(className, varName, ...) \
    className varName; \
    ctorName(&varName, ## __VA_ARGS__)

/// 无法在退出作用域时自动销毁对象 (需要手动调用)
#define obj_destroy(className, varName) \
    dtorName(&varName)

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define obj_new(className, varName, ...) \
    className *varName = calloc(1, sizeof(struct className)); \
    if (varName) ctorName(varName, ## __VA_ARGS__)

#define obj_delete(className, varName) \
    if (varName) {dtorName(varName); free(varName);}

#endif //TEST_C_OOP_H
