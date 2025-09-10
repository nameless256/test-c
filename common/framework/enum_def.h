//
// Created by xiaoxianghui on 2025/9/8.
//

#ifndef TEST_C_ENUM_DEF_H
#define TEST_C_ENUM_DEF_H

#ifndef getVaCount
#define _getVaCount(_1, _2, _3, _4, _5, N, ...) N
#define getVaCount(...) _getVaCount(__VA_ARGS__, 5, 4, 3, 2, 1)
#endif

#ifndef cat2
#define _cat2(a, b) a ## b
#define cat2(a, b) _cat2(a, b)
#endif

#define enumValDefArg1(name) name
#define enumValDefArg2(name, init) name = (init)
#define enumValDef(...) cat2(enumValDefArg, getVaCount(__VA_ARGS__)) (__VA_ARGS__),
#define enumValCapture(name, ...) name2StrCase(name);
#define enumIter(action, name) enumIter ## _ ## name(action, name)
#define enumDispatch(action, prefix, name, ...) action(prefix ## _ ## name, ## __VA_ARGS__)

#define enumDefArg1(name) typedef enum { enumIter(enumValDef, name) } (name);
#define enumDefArg2(name, base) enum { enumIter(enumValDef, name) }; typedef base name;

/**
 * @example
 * ```c
 * #define enumIter_fieldTypeId(action, prefix) \
 * enumDispatch(action, prefix, Int, 0) \
 * enumDispatch(action, prefix, Float) \
 * enumDispatch(action, prefix, Double) \
 * enumDispatch(action, prefix, Ptr) \
 * enumDispatch(action, prefix, Array) \
 * enumDispatch(action, prefix, Enum) \
 * enumDispatch(action, prefix, Bool) \
 * enumDispatch(action, prefix, Bits)
 *
 * enumDef(fieldTypeId, uint8_t)
 * enumDefToStr(fieldTypeId)
 * ```
 */
#define enumDef(...) cat2(enumDefArg, getVaCount(__VA_ARGS__)) (__VA_ARGS__)
#define enumDefToStr(name) \
static inline char *name ## _ ## toString(name val) { \
    switch(val) { enumIter(enumValCapture, name) default: return "NaN"; } \
};

#endif //TEST_C_ENUM_DEF_H
