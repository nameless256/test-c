//
// Created by CodingDev on 2026/2/26.
//

#include "util.h"

typedef struct vectorMeta {
    size_t capacity;
    size_t size;
} vectorMeta;

#define vector_getMeta(n) (((vectorMeta *)(n)) - 1)

#define _vector2(t, n, c, v)                                                     \
t *n __attribute__((cleanup(vector_dtor))) = NULL;                               \
do {                                                                             \
    n = (t *) (((vectorMeta *) malloc(sizeof(vectorMeta) + sizeof(t) * c)) + 1); \
    if (vector_getMeta(n) == NULL) { n = NULL; break; }                          \
    vector_capacity(n) = c;                                                      \
    vector_size(n) = c;                                                          \
    if (c == 0) break;                                                           \
    n[0] = v;                                                                    \
    fillMemoryWithPattern(n, sizeof(t), c, &n[0]);                               \
} while (0)
#define _vector1(t, n, c) _vector2(t, n, c, 0)
#define _vector0(t, n) _vector1(t, n, 0)
#define vector(t, n, ...) cat2(_vector, mcrVaCount(__VA_ARGS__)) (t, n, ##__VA_ARGS__)

void vector_dtor(void *self);

#define vector_capacity(v) vector_getMeta(v)->capacity
#define vector_size(v) vector_getMeta(v)->size
#define vector_empty(v) (vector_size(v) == 0)
/// \todo 异常机制的实现及抛出
#define vector_at(v, i) *(i < vector_size(v) ? &v[i] : NULL)
#define vector_front(v) vector_at(v, 0)
#define vector_back(v) vector_at(v, vector_size(v) - 1)
#define vector_data(v) v
