//
// Created by CodingDev on 2026/2/26.
//

#if !defined(VECTOR_BASE_H) || \
(defined(VECTOR_BASE_H) && defined(classVtabDecl)) || \
(defined(VECTOR_BASE_H) && defined(classVtabBind))
#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H
#endif

#include "access_ctrl.h"
#define className vector_base

typedef struct className className;

accessStart
#undef accessLv
#define accessLv $public
bind(copy)
bind(dtor)
export(size_t, capacity)
export(size_t, size)
export(bool, empty)
export(void *, at, size_t elmSize, int idx)
export(void *, tail, size_t elmSize)
export(void *, head)
export(void *, data)
export(bool, reserve, size_t elmSize, size_t capacity)
export(bool, addTail, size_t elmSize, void *elm)
export(void, delTail, size_t elmSize)
export(bool, add, size_t elmSize, int idx, size_t count, void *elm)
export(void, del, size_t elmSize, int idx, size_t count)
export(void, clear, size_t elmSize)
export(bool, resize, size_t elmSize, void *elm, size_t count)
export(void, swap, className *other)
accessEnd

#include "clean_up_method.h"

#ifndef classVtabDecl
#ifndef classVtabBind
#define classVtabDecl
#include "vector_base.h"

#if accessCtrl == $private
#undef accessCtrl
#define accessCtrl $protected
#endif

// 包含基类

#include "def_class.h"
#else
#include "reg_meta_class.h"
#endif
#define className vector_base
#define classBase objBase
classStart
    classEntry(size_t capacity, capacity)
    classEntry(size_t size, size)
    classEntry(void *data, data)
classEnd

#include "clean_up_class.h"

#endif

#endif
