//
// Created by xiaoxianghui on 2025/4/9.
//

#ifndef TEST_C_LIST_BASE_H
#define TEST_C_LIST_BASE_H

//以下是 `std::list` 各函数的分类及简要说明：
//
//---
//
//### **1. 构造/析构**
//- **`list()`**：创建空链表。
//- **`list(size_type count, const T& value)`**：创建含 `count` 个 `value` 的链表。
//- **`explicit list(size_type count)`**：创建含 `count` 个默认初始化元素的链表。
//- **`list(const list& other)`**：拷贝构造链表。
//- **`list(list&& other)`**：移动构造链表（C++11）。
//- **`list(initializer_list<T> init)`**：用初始化列表构造链表（C++11）。
//- **`~list()`**：析构函数，释放链表内存。
//
//---
//
//### **2. 元素访问**
//- **`front()`** → `T&`：返回首元素的引用（空链表时未定义）。
//- **`back()`** → `T&`：返回尾元素的引用（空链表时未定义）。
//
//---
//
//### **3. 迭代器**
//- **`begin()/end()`** → 双向迭代器：指向首元素和尾后位置。
//- **`cbegin()/cend()`** → 常量迭代器（C++11）。
//- **`rbegin()/rend()`** → 反向迭代器：从尾到头遍历。
//- **`crbegin()/crend()`** → 常量反向迭代器（C++11）。
//
//---
//
//### **4. 容量**
//- **`empty()`** → `bool`：判断链表是否为空（O(1)）。
//- **`size()`** → `size_type`：返回元素数量（O(n) C++11 前，可能 O(1) 后）。
//- **`max_size()`** → `size_type`：返回可容纳的最大元素数。
//
//---
//
//### **5. 修改器**
//- **`clear()`**：删除所有元素（O(n)）。
//- **`insert(iterator pos, const T& value)`** → 迭代器：在 `pos` 前插入元素。
//- **`emplace(iterator pos, Args&&... args)`** → 迭代器：原位构造插入元素（C++11）。
//- **`erase(iterator pos)`** → 迭代器：删除 `pos` 处元素。
//- **`push_back(const T& value)`**：尾部插入元素（O(1)）。
//- **`push_front(const T& value)`**：头部插入元素（O(1)）。
//- **`pop_back()`**：删除尾部元素（空链表时未定义）。
//- **`pop_front()`**：删除头部元素（空链表时未定义）。
//- **`emplace_back(Args&&... args)`**：尾部原位构造元素（C++11）。
//- **`emplace_front(Args&&... args)`**：头部原位构造元素（C++11）。
//- **`resize(size_type count)`**：调整链表大小为 `count`，新增元素默认初始化。
//- **`swap(list& other)`**：交换两个链表内容（O(1)）。
//
//---
//
//### **6. 链表特有操作**
//- **`splice(iterator pos, list& other)`**：将 `other` 所有元素移动到当前链表 `pos` 前（O(1)）。
//- **`merge(list& other)`**：合并两个有序链表（`other` 会被清空）。
//- **`remove(const T& value)`**：删除所有等于 `value` 的元素（O(n)）。
//- **`remove_if(Predicate pred)`**：删除满足条件 `pred` 的元素（O(n)）。
//- **`reverse()`**：反转链表元素顺序（O(n)）。
//- **`sort()`**：默认升序排序（时间复杂度 O(n log n)）。
//- **`unique()`**：删除连续重复元素（通常与 `sort` 配合去重）。
//
//---
//
//📌 **关键特性**：
//所有插入/删除操作（如 `push_back`、`splice`）的时间复杂度为 **O(1)**，但 `size()` 在 C++11 前可能为 O(n)。

#include "oop.h"

/**
 * 实现类型擦除的共用list
 * 特定类型list定义宏
 * 通过函数指针特化类型
 */

#endif //TEST_C_LIST_BASE_H
