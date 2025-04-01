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

/******************************************************************/ // { 完整对象声明支持 }

/**
 * @details 空类的对象占用 1 字节的原因是为了保证每个对象在内存中有唯一的地址。
 * @details 这是 C++ 标准的规定，以确保即使对于空类，不同对象的指针也可以区分。
 * @details 空的结构体（struct）在 C++ 中也是同样的处理方式，即占用 1 字节。
 * @details 这是因为 struct 和 class 在 C++ 中除了默认访问控制外，其他方面几乎相同。
 * @details 这种设计有助于避免多个空对象实例共享同一个地址，从而简化了指针和引用的管理，特别是在多态和继承的情况下。
 */
#define oopClassDef \
struct className; \
typedef struct className className; \
struct className { \
    union { \
        char _; \
        struct { \
            classBaseName classBaseName;

#define oopClassDefEnd \
        }; \
    }; \
};

/******************************************************************/ // [ 虚函数 ] 的 声明 及 定义

#define oopVTabName(className) CONCAT3(className, _, vTab)

#define oopVPtrDef struct oopVTabName(className) {

#define oopVPtrDefEnd } const *vptr;

#define oopVTab(className) \
static struct oopVTabName(className) oopVTabName(className)

#define oopVFuncDeclare(returnType, methodName, ...) \
returnType (*methodName)(className *self, ## __VA_ARGS__)

#define oopVCtorDeclare(...) void (*ctor)(className *self, ## __VA_ARGS__)
#define oopVDtorDeclare() void (*dtor)(className *self)

#define oopVPtrInit() \
    self->vptr = &oopVTabName(className)

#define oopVPtrBaseInit() \
    oopVTabName(classBaseName) = *self->classBaseName.vptr; \
    self->classBaseName.vptr = &oopVTabName(classBaseName)

#define oopVFuncBinding(methodName) \
    oopVTabName(className).methodName = methodName

#define oopVFuncOverride(methodName) \
    oopVTabName(classBaseName).methodName = (void *) methodName

/// 需要套层壳包装虚函数具体实现的调用, 并通过壳的声明位置决定作用域是 公共、私有还是受保护
#define oopVFuncImpl(returnType, methodName, ...) \
static returnType methodName(className *self, ## __VA_ARGS__)

/******************************************************************/ // [ 构造 / 析构 ] 的 声明 及 定义

/// 无法支持重载, 无论是通过 宏魔法 (Morn 库 的思路) 还是 可变参 都需要 手动增加代码, 往往还不利于维护, 甚至隐藏风险
#define oopCtor(...) void CONCAT3(className, _, ctor)(className *self, ## __VA_ARGS__)

#define oopCtorBaseCall(...) CONCAT3(classBaseName, _, ctor)((classBaseName *)self, ## __VA_ARGS__)

#define oopDtor() void CONCAT3(className, _, dtor)(className *self)

#define oopDtorBaseCall() CONCAT3(classBaseName, _, dtor)((classBaseName *)self)

/******************************************************************/ // 在栈上 [ 创建 / 销毁 ] 对象

/// 全局对象 的 构造析构 需要在 程序开始 及 结束时 手动调用 略显麻烦 且 不方便使用 这是一个无法避免的痛点
/// 且 __attribute__((cleanup(CONCAT3(className, _, dtor)))) 在 有 goto语句 的函数上可能会报错
/// 借助 GCC 的 __attribute__((cleanup())) 实现
#define oopObj(className, varName, ...) \
    className varName __attribute__((cleanup(CONCAT3(className, _, dtor)))); \
    CONCAT3(className, _, ctor)(&varName, ## __VA_ARGS__)

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define oopObjNew(className, varName, ...) \
    varName = CONCAT3(className, _, memAlloc)(); \
    do {if (varName) CONCAT3(className, _, ctor)(varName, ## __VA_ARGS__);} while (0)

#define oopObjDelete(className, varName) \
    do {if (varName) {CONCAT3(className, _, dtor)(varName); CONCAT3(className, _, memFree)(varName);}} while (0)

/******************************************************************/ // { 简洁封装支持 }

/**
 * @details 为在C语言下确保封装及简洁，在public.h声明，在源文件定义
 * @details 因定义位置变更，无法支持继承、虚表及栈上创建对象
 */
#define oopClassDeclare() \
struct className; \
typedef struct className className;

#define oopClassDefine() \
struct className

#define oopInherit() classBaseName *base

/******************************************************************/ // [ 创建 / 销毁 ] 的 声明 及 定义

#define oopCreate(...) \
    className *CONCAT3(className, _, create)(__VA_ARGS__)

#define oopDestroy() \
    void CONCAT3(className, _, destroy)(className *self)

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define oopObjCreate(className, varName) \
    varName = CONCAT3(className, _, create)

#define oopObjDestroy(className, varName) \
    CONCAT3(className, _, destroy)(varName)

/******************************************************************/ // { 公共定义 }

#define oopMemAlloc malloc

#define oopMemFree free

/******************************************************************/ // [ 成员变量 访问器 ] 的 声明 及 定义

#define oopVarAccessor(type, varName) \
static inline type CONCAT3(className, _get_, varName)(className *self) { return self->varName; } \
static inline void CONCAT3(className, _set_, varName)(className *self, type val) { self->varName = val; }

/******************************************************************/ // [ 成员函数 ] 的 声明 及 定义

#define oopFunc(returnType, methodName, ...) \
returnType methodName(className *self, ## __VA_ARGS__)

#define oopFuncPublic(returnType, methodName, ...) \
oopFunc(returnType, CONCAT3(className, _, methodName), ## __VA_ARGS__)

#define oopFuncProtected(returnType, methodName, ...) \
oopFuncPublic(returnType, methodName, ## __VA_ARGS__)

#define oopFuncPrivate(returnType, methodName, ...) \
static oopFunc(returnType, methodName, ## __VA_ARGS__)

/******************************************************************/ // 引用

/// 相对鸡肋
#define oopRef(arg) (&(arg))
#define oopQuote(arg) (*const (arg))
#define oopDequote(arg) (*(arg))

#endif //TEST_C_OOP_H
