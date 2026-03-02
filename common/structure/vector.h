//
// Created by CodingDev on 2026/2/26.
//

#include "util.h"
#include "type_meta.h"

typedef struct vectorMeta {
    size_t capacity;
    size_t typeSize; ///< \todo 改成通过反射获取的类型元数据
    size_t size;
} vectorMeta;

#define vector_getMeta(n) (((vectorMeta *)(n)) - 1)

/// \todo alloc_safe return true 时异常抛出
/// \todo 复杂对象析构及拷贝
#define _vector_ctor2(n, c, v)                                                   \
do {                                                                             \
    (n) = NULL;                                                                  \
    if (alloc_safe((void **) &(n), sizeof(*(n)) * c, sizeof(vectorMeta))) break; \
    vector_capacity(n) = c;                                                      \
    vector_size(n) = c;                                                          \
    vector_getMeta(n)->typeSize = sizeof(*(n));                                  \
    if (c == 0) break;                                                           \
    (n)[0] = v;                                                                  \
    fillMemoryWithPattern(n, sizeof(*(n)), c, &(n)[0]);                          \
} while (0)
#define _vector_ctor1(n, c) _vector_ctor2(n, c, 0)
#define _vector_ctor0(n) _vector_ctor1(n, 0)
#define vector_ctor(n, ...) cat2(_vector_ctor, mcrVaCount(__VA_ARGS__)) (n, ##__VA_ARGS__)

#define vector(t, n, ...)                      \
t *n __attribute__((cleanup(vector_cleanup))); \
vector_ctor(n, ##__VA_ARGS__);

void vector_dtor(void *v);

void vector_cleanup(void *p2p);

#define vector_capacity(v) vector_getMeta(v)->capacity
#define vector_size(v) vector_getMeta(v)->size
#define vector_empty(v) (vector_size(v) == 0)

/// \todo NULL 时异常抛出
#define vector_at(v, i) *(i < vector_size(v) ? &(v)[i] : NULL)
#define vector_front(v) vector_at(v, 0)
#define vector_back(v) vector_at(v, vector_size(v) - 1)
#define vector_data(v) (v)

void vector_reserve(void *v, size_t c);
