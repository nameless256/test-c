//
// Created by CodingDev on 2026/2/26.
//

#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include "util.h"
#include "meta.h"

#define className vector_base
#define classMember(f) \
mcrDispatch(f, base, objBase base) \
mcrDispatch(f, capacity, size_t capacity) \
mcrDispatch(f, size, size_t size) \
mcrDispatch(f, data, void *data)
#ifdef VECTOR_BASE_H_IMPL
#define classMataRemain
#endif
#include "def_class.h"

#ifdef VECTOR_BASE_H_IMPL
#include "def_meta_class.h"
#endif

#define className vector_base

export(size_t, capacity);
export(size_t, size);
export(bool, empty);
export(void *, at, int idx, size_t elmSize);
export(void *, tail, size_t elmSize);
export(void *, head);
export(void *, data);
export(bool, reserve, size_t capacity, size_t elmSize);
export(bool, addTail, bool isClass, size_t elmSize, void *elm);
export(void *, delTail, bool isClass, size_t elmSize);
//插入位置	v.insert(it, x)	v.insert(idx, x)
//删除位置	v.erase(it)	v.remove(idx) → T
//清空	    v.clear()	v.clear()
//调整大小	v.resize(n, val)	v.resize(n, val)
//交换内容	v.swap(other)	std::mem::swap(&mut v, &mut other)
//缩减容量

#ifdef VECTOR_BASE_H_IMPL
#undef VECTOR_BASE_H_IMPL
#endif

#undef className

#endif
