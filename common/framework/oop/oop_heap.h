//
// Created by xiaoxianghui on 2025/3/29.
//

#ifndef TEST_C_OOP_HEAP_H
#define TEST_C_OOP_HEAP_H

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
 * @details 为在C语言下确保封装及简洁，在public.h声明，在源文件定义
 * @details 因定义位置变更，无法支持虚表及栈上创建对象
 */
#define classDeclare() \
struct className; \
typedef struct className className;

#define classDefine() \
struct className

#define inherit() classBaseName classBaseName;

/******************************************************************/ // [ 成员变量 访问器 ] 的 声明 及 定义

#define mVarAccessor(type, varName) \
static inline type CONCAT3(className, _get_, varName)(className *self) { return self->varName; } \
static inline void CONCAT3(className, _set_, varName)(className *self, type val) { self->varName = val; }

/******************************************************************/ // [ 成员函数 ] 的 声明 及 定义

#define mFunc(returnType, methodName, ...) \
returnType methodName(className *self, ## __VA_ARGS__)

#define mFuncPublic(returnType, methodName, ...) \
mFunc(returnType, CONCAT3(className, _, methodName), ## __VA_ARGS__)

#define mFuncProtected(returnType, methodName, ...) \
mFuncPublic(returnType, methodName, ## __VA_ARGS__)

#define mFuncPrivate(returnType, methodName, ...) \
static mFunc(returnType, methodName, ## __VA_ARGS__)

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

/******************************************************************/ // 在堆上 [ 创建 / 销毁 ] 对象

#define objNew(className, varName, ...) \
    className *varName = calloc(1, sizeof(struct className)); \
    if (varName) CONCAT3(className, _, ctor)(varName, ## __VA_ARGS__)

#define objDelete(className, varName) \
    if (varName) {CONCAT3(className, _, dtor)(varName); free(varName);}

/******************************************************************/ // 引用

/// 相对鸡肋
#define ref(arg) (&(arg))
#define quote(arg) (*const (arg))
#define dequote(arg) (*(arg))

#endif //TEST_C_OOP_HEAP_H
