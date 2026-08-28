//
// Created by CodingDev on 2026/2/26.
//

#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include "obj.h"

#define className vector_base
#define classMember(f) \
mcrDispatch(f, capacity, size_t capacity) \
mcrDispatch(f, size, size_t size) \
mcrDispatch(f, data, void *data)
#ifdef VECTOR_BASE_H_IMPL
//#define classMataRemain
#endif
#include "def_class.h"

#ifdef VECTOR_BASE_H_IMPL
#define classCopy
#define classDtor
#include "reg_meta_class.h"
#include "class_vector_base.h"
#endif

#define className vector_base

export(size_t, capacity);
export(size_t, size);
export(bool, empty);
export(void *, at, size_t elmSize, int idx);
export(void *, tail, size_t elmSize);
export(void *, head);
export(void *, data);
export(bool, reserve, size_t elmSize, size_t capacity);
export(bool, addTail, size_t elmSize, void *elm);
export(void, delTail, size_t elmSize);
export(bool, add, size_t elmSize, int idx, size_t count, void *elm);
export(void, del, size_t elmSize, int idx, size_t count);
export(void, clear, size_t elmSize);
export(bool, resize, size_t elmSize, void *elm, size_t count);
export(void, swap, className *other);

#undef className

#ifdef VECTOR_BASE_H_IMPL
#undef VECTOR_BASE_H_IMPL
#endif

#endif
