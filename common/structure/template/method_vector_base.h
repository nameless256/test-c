//
// Created by CodingDev on 2026/8/29.
//

#include "access_ctrl.h"
#define className vector_base
public(size_t, capacity);
public(size_t, size);
public(bool, empty);
public(void *, at, size_t elmSize, int idx);
public(void *, tail, size_t elmSize);
public(void *, head);
public(void *, data);
public(bool, reserve, size_t elmSize, size_t capacity);
public(bool, addTail, size_t elmSize, void *elm);
public(void, delTail, size_t elmSize);
public(bool, add, size_t elmSize, int idx, size_t count, void *elm);
public(void, del, size_t elmSize, int idx, size_t count);
public(void, clear, size_t elmSize);
public(bool, resize, size_t elmSize, void *elm, size_t count);
public(void, swap, className *other);

#include "clean_up_method.h"
