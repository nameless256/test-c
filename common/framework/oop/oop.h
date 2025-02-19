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
 * @warning 虽然说可以直接访问成员变量 但不推荐 本质上是绕过了封装 导致原有的访问控制的方法失效了
 * @warning 建议 通过 访问器 来 访问 成员变量
 * @warning 没有 对应 虚函数实现 的 类(抽象类) 不能 实例化 虽然没有做实际限制 但通过多态调用时 可能会调用空指针
 */

/**
 * @details 空类的对象占用 1 字节的原因是为了保证每个对象在内存中有唯一的地址。
 * @details 这是 C++ 标准的规定，以确保即使对于空类，不同对象的指针也可以区分。
 * @details 空的结构体（struct）在 C++ 中也是同样的处理方式，即占用 1 字节。
 * @details 这是因为 struct 和 class 在 C++ 中除了默认访问控制外，其他方面几乎相同。
 * @details 这种设计有助于避免多个空对象实例共享同一个地址，从而简化了指针和引用的管理，特别是在多态和继承的情况下。
 */
#define classDef \
struct className; \
typedef struct className className; \
struct className { \
    union { \
        char _; \
        struct { \
            classBaseName classBaseName;

#define classDefEnd \
        }; \
    }; \
};

/******************************************************************/ // [ 成员函数 ] 的 声明 及 定义

#define mFuncName(methodName) CONCAT3(className, _, methodName)
#define mFuncCall(methodName, ...) mFuncName(methodName)(self, ## __VA_ARGS__)

#define mFuncBaseName(methodName) CONCAT3(classBaseName, _, methodName)
#define mFuncBaseCall(methodName, ...) mFuncBaseName(methodName)(&self->classBaseName, ## __VA_ARGS__)

#define mFuncDeclare(returnType, methodName, ...) \
returnType mFuncName(methodName)(className *self, ## __VA_ARGS__)
#define mFuncDefine(returnType, methodName, ...) \
mFuncDeclare(returnType, methodName, ## __VA_ARGS__)

/******************************************************************/ // [ 虚函数 ] 的 声明 及 定义

#define vFuncTabName(className) CONCAT3(className, _, vFuncTab)

#define vPtrDef struct vFuncTabName(className) {

#define vPtrDefEnd } const *vptr;

#define vFuncTabDefine(className) \
static struct vFuncTabName(className) vFuncTabName(className)

#define vFuncDeclare(returnType, methodName, ...) \
returnType (*methodName)(className *self, ## __VA_ARGS__)

#define vCtorDeclare(...) void (*ctor)(className *self, ## __VA_ARGS__)
#define vDtorDeclare() void (*dtor)(className *self)

#define vptrInit() \
    self->vptr = &vFuncTabName(className)

#define vptrBaseInit() \
    vFuncTabName(classBaseName) = *self->classBaseName.vptr; \
    self->classBaseName.vptr = &vFuncTabName(classBaseName)

#define vFuncBinding(className, methodName) \
    vFuncTabName(className).methodName = methodName

/// 需要套层壳包装虚函数具体实现的调用, 并通过壳的声明位置决定作用域是 公共、私有还是受保护
#define vFuncImplement(returnType, methodName, vFuncClassName, ...) \
static returnType methodName(vFuncClassName *self, ## __VA_ARGS__)

/******************************************************************/ // [ 成员变量 访问器 ] 的 声明 及 定义

#define mVarDeclare(type, varName) \
type CONCAT3(className, _get_, varName)(className *self); \
void CONCAT3(className, _set_, varName)(className *self, type val);

#define mVarDefine(type, varName) \
type CONCAT3(className, _get_, varName)(className *self) { return self->varName; } \
void CONCAT3(className, _set_, varName)(className *self, type val) { self->varName = val; }

/******************************************************************/ // [ 构造 / 析构 ] 的 声明 及 定义

/// 无法支持重载, 无论是通过 宏魔法 (Morn 库 的思路) 还是 可变参 都需要 手动增加代码, 往往还不利于维护, 甚至隐藏风险
#define ctorName CONCAT3(className, _, ctor)
#define ctorDeclare(...) void ctorName(className *self, ## __VA_ARGS__)
#define ctorDefine(...) ctorDeclare(__VA_ARGS__)

#define ctorBaseCall(...) CONCAT3(classBaseName, _, ctor)((classBaseName *)self, ## __VA_ARGS__)

#define dtorName CONCAT3(className, _, dtor)
#define dtorDeclare() void dtorName(className *self)
#define dtorDefine() dtorDeclare()

#define dtorBaseCall() CONCAT3(classBaseName, _, dtor)((classBaseName *)self)

/******************************************************************/ // 在栈上 [ 创建 / 销毁 ] 对象

/// 全局对象 的 构造析构 需要在 程序开始 及 结束时 手动调用 略显麻烦 且 不方便使用 这是一个无法避免的痛点
/// 且 __attribute__((cleanup(CONCAT3(className, _, dtor)))) 在 有 goto语句 的函数上可能会报错 这也是一个无法避免的痛点
#if 1
/// 借助 GCC 的 __attribute__((cleanup())) 实现
#define obj_create(className, varName, ...) \
    className varName __attribute__((cleanup(CONCAT3(className, _, dtor)))); \
    CONCAT3(className, _, ctor)(&varName, ## __VA_ARGS__)
#else
#define obj_create(className, varName, ...) \
    className varName; \
    CONCAT3(className, _, ctor)(&varName, ## __VA_ARGS__)

/// 无法在退出作用域时自动销毁对象 (需要手动调用)
#define obj_destroy(className, varName) \
    CONCAT3(className, _, dtor)(&varName)
#endif

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define obj_new(className, varName, ...) \
    className *varName = calloc(1, sizeof(struct className)); \
    if (varName) CONCAT3(className, _, ctor)(varName, ## __VA_ARGS__)

#define obj_delete(className, varName) \
    if (varName) {CONCAT3(className, _, dtor)(varName); free(varName);}

#endif //TEST_C_OOP_H
