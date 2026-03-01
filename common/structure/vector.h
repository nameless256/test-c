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
#define _vector2(t, n, c, v)                                                     \
t *n __attribute__((cleanup(vector_cleanup))) = NULL;                            \
do {                                                                             \
    if (alloc_safe((void **) &n, sizeof(t) * c, sizeof(vectorMeta))) break;      \
    vector_capacity(n) = c;                                                      \
    vector_size(n) = c;                                                          \
    vector_getMeta(n)->typeSize;                                                 \
    if (c == 0) break;                                                           \
    n[0] = v;                                                                    \
    fillMemoryWithPattern(n, sizeof(t), c, &n[0]);                               \
} while (0)
#define _vector1(t, n, c) _vector2(t, n, c, 0)
#define _vector0(t, n) _vector1(t, n, 0)
#define vector(t, n, ...) cat2(_vector, mcrVaCount(__VA_ARGS__)) (t, n, ##__VA_ARGS__)

void vector_cleanup(void *p2p);

#define vector_capacity(v) vector_getMeta(v)->capacity
#define vector_size(v) vector_getMeta(v)->size
#define vector_empty(v) (vector_size(v) == 0)

/// \todo NULL 时异常抛出
#define vector_at(v, i) *(i < vector_size(v) ? &v[i] : NULL)
#define vector_front(v) vector_at(v, 0)
#define vector_back(v) vector_at(v, vector_size(v) - 1)
#define vector_data(v) v

void vector_reserve(void *v, size_t c) {
    if (c == vector_capacity(v)) return;
    size_t ex = vector_capacity(v) + (vector_capacity(v) >> 1);
    if (ex < c) ex = c;
    /// \todo alloc_safe return true 时异常抛出
    if (alloc_safe((void **) &v, vector_getMeta(v)->typeSize * ex, sizeof(vectorMeta))) return;
    vector_capacity(v) = ex;
}
