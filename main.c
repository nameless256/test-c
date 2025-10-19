/**
 *****************************************************************************************
 * Copyright(c) 20XX, XXX Corporation. All rights reserved.
 *****************************************************************************************
 * @file    main.c
 * @brief
 * @author
 * @date
 * @version 0.0.1
 *****************************************************************************************
 * @attention
 * <h2><center>&copy; COPYRIGHT 20XX XXX Corporation</center></h2>
 *****************************************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "oop_heap_usage.h"
#include "oop_usage.h"
#include "util.h"
#include "unicode.h"

/**
 * @defgroup Main
 * @{
 */

#define sumDef(type) type sum_##type(type arg0, type arg1)
#define sumDefBase(type) type sum_##type(type arg0, type arg1) { return arg0 + arg1; }
#define sum(type) sum_##type

sumDefBase(double)

sumDefBase(int)

typedef struct {
    double f;
    int i;
} testStruct;

sumDef(testStruct) {
    return (testStruct) {sum(double)(arg0.f, arg1.f), sum(int)(arg0.i, arg1.i)};
}

#include "enum_def.h"

#define enumIter_fieldTypeId(action, prefix) \
enumDispatch(action, prefix, Int, 0) \
enumDispatch(action, prefix, Float) \
enumDispatch(action, prefix, Double) \
enumDispatch(action, prefix, Ptr) \
enumDispatch(action, prefix, Array) \
enumDispatch(action, prefix, Enum) \
enumDispatch(action, prefix, Bool) \
enumDispatch(action, prefix, Bits)

enumDef(fieldTypeId)
enumDefToStr(fieldTypeId)

typedef struct _typeMetaBase typeMetaBase;
struct _typeMetaBase {
    const char *name;
    size_t size;
};

typedef struct _enumValMetaBase enumValMetaBase;
struct _enumValMetaBase {
    int idx;
    char *name;
};

typedef struct _enumMeta enumMeta;
struct _enumMeta {
    char *name;
    size_t size;
    char *baseType;
    int count;
    enumValMetaBase **list;
};

enum _temp {
    temp_0 = 2,
    temp_1,
    temp_2,
};

typedef uint8_t temp;

struct _enumValMeta_temp {
    enumValMetaBase base;
    uint8_t val;
};

typedef struct _enumValMeta_temp enumValMeta_temp;

#define _enumIter(f, ...) mcrIter(f, succ, 0, __VA_ARGS__)

#define enumValMetaDef(idx, arg) enumValMeta_temp enumValMeta##_##arg = {{idx, #arg}, arg};

_enumIter(
    enumValMetaDef,
    temp_0,
    temp_1,
    temp_2
)

enumValMetaBase *temp_list[] = {
    (enumValMetaBase *)&enumValMeta_temp_0,
    (enumValMetaBase *)&enumValMeta_temp_1,
    (enumValMetaBase *)&enumValMeta_temp_2,
};

enumMeta temp_meta = {
    "temp", "uint8_t", sizeof(uint8_t), ARRAY_SIZE(temp_list), temp_list
};

#define MATCH_$ ,_arg
#define MATCH_$__2(a, ...) a
#define MATCH_$__3(...) *
#define _CONVERT_$(...) CAT_2(MATCH_$_, vaCount(__VA_ARGS__))(__VA_ARGS__)
#define CONVERT_$(a) _CONVERT_$(a, CAT_2(MATCH,a))

//CONVERT_$(const)
//CONVERT_$($)

// 辅助宏：拼接两个标记
#define _CAT_2(a, b) a##_##b
#define CAT_2(a, b) _CAT_2(a, b)

// 根据参数数量调用对应的处理宏
#define SNAKE_CASE_1(a) a
#define SNAKE_CASE_2(a, ...) CAT_2(a, SNAKE_CASE_1(__VA_ARGS__))
#define SNAKE_CASE_3(a, ...) CAT_2(a, SNAKE_CASE_2(__VA_ARGS__))
#define SNAKE_CASE_4(a, ...) CAT_2(a, SNAKE_CASE_3(__VA_ARGS__))
#define SNAKE_CASE_5(a, ...) CAT_2(a, SNAKE_CASE_4(__VA_ARGS__))

// 主宏：将参数拼接为蛇形命名
#define SNAKE_CASE(...) \
    CAT_2(SNAKE_CASE, vaCount(__VA_ARGS__))(__VA_ARGS__)

//SNAKE_CASE(const, struct, typeInfo, $)
//SNAKE_CASE(const, struct, typeInfo)
//const_struct_typeInfo_$

//#define PTR_CAST(x)
#define VA_ARG2STR_0(ARG, ...) ARG VA_ARG2STR_1(__VA_ARGS__)
#define VA_ARG2STR_1(ARG, ...) ARG VA_ARG2STR_2(__VA_ARGS__)
#define VA_ARG2STR_2(ARG, ...) ARG VA_ARG2STR_3(__VA_ARGS__)
#define VA_ARG2STR_3(ARG, ...) ARG
#define VA_ARG2STR(...) nameVal2Str(VA_ARG2STR_0(__VA_ARGS__))
#define VA_ARG2TYPE(...) VA_ARG2STR_0(__VA_ARGS__)
//VA_ARG2STR(const, struct, typeInfo, $)
//"const struct typeInfo *"
//VA_ARG2TYPE(const, struct, typeInfo, $)
//const struct typeInfo *

int main() {
    system("chcp 65001");
    clock_t start = clock();
    fieldTypeId o = fieldTypeId_Int;
    fieldTypeId_toString(o);
//    oopHeapUsage();
//    oopUsage();
    printf("[%d] --------- {%s} %d %f \n", __LINE__, __FUNCTION__, sum(int)(2, 9), sum(double)(3.14, 2.96));

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
//    system("pause");
    return 0;
}

/** @} */
