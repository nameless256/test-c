//
// Created by CodingDev on 2026/8/29.
//

#define className vector_base
methodStart
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
methodEnd

#include "clean_up_method.h"
