//
// Created by CodingDev on 2026/2/26.
//

#include "util.h"

typedef struct vectorMeta {
    size_t capacity;
    size_t size;
} vectorMeta;

#define vectorGetMeta(n) ((vectorMeta *)((n) - 1))
#define vectorGetdata(t, m) (t *)((vectorMeta *)(m) + 1)

#define _vector2(t, n, c, v)                                          \
t *n __attribute__((cleanup(vector_dtor))) = NULL;                    \
do {                                                                  \
n = vectorGetdata(t, malloc(sizeof(vectorMeta) + sizeof(t) * c)); \
if (n == NULL || vectorGetMeta(n) == NULL) {                      \
n = NULL;                                                     \
break;                                                        \
}                                                                 \
vectorGetMeta(n)->capacity = c;                                   \
vectorGetMeta(n)->size = c;                                       \
if (c == 0) break;                                                \
n[0] = v;                                                         \
fillMemoryWithPattern(n, sizeof(t), c, &n[0]);                    \
} while (0)
#define _vector1(t, n, c) _vector2(t, n, c, 0)
#define _vector0(t, n) _vector1(t, n, 0)
#define vector(t, n, ...) cat2(_vector, mcrVaCount(__VA_ARGS__)) (t, n, ##__VA_ARGS__)

#define vector_size(v) vectorGetMeta(v)->size
/// \todo 异常机制的实现及抛出
#define vector_at(v, i) *(i < vector_size(v) ? &v[i] : NULL)

void vector_dtor(void *self);
