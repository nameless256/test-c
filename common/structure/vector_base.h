//
// Created by CodingDev on 2026/2/26.
//

#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include "util.h"
#include "meta.h"

#define className vector_base
#define classMember(f) \
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
export(bool, reserve, size_t capacity, size_t elmSize);

#ifdef VECTOR_BASE_H_IMPL
#undef VECTOR_BASE_H_IMPL
#endif

#undef className

#endif
