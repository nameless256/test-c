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

#define enumIter_fieldTypeId(prefix, action) \
enumDispatch(action, prefix, Int, = 0) \
enumDispatch(action, prefix, Float) \
enumDispatch(action, prefix, Double) \
enumDispatch(action, prefix, Ptr) \
enumDispatch(action, prefix, Array) \
enumDispatch(action, prefix, Enum) \
enumDispatch(action, prefix, Bool) \
enumDispatch(action, prefix, Bits)

enumDef(fieldTypeId)
enumDefToStr(fieldTypeId)

struct typeInfo;
typedef struct typeInfo typeInfo;

typedef struct {
    fieldTypeId id;
    const struct typeInfo *type;
    const char *name;
    size_t offset;
    size_t length;
} fieldInfo;

struct typeInfo {
    const char *name;
    size_t size;
    size_t sizePacked;
    size_t fieldsLength;
    const fieldInfo *fields;
    bool isSigned;
};

#define IS_DOLLAR_IMPL(x)  IS_DOLLAR_IMPL2(x)
#define IS_DOLLAR_IMPL2(x) IS_DOLLAR_##x

#define IS_DOLLAR(x)       IS_DOLLAR_IMPL(x)
#define IS_DOLLAR_$        *

// 通用宏：如果参数是 $，转成 *，否则原样输出
#define CONVERT_DOLLAR_TO_STAR(x)  IF_EQ(x, $)

// 辅助宏定义
#define IF_EQ(a, b)   IF_EQ_1(a, b)
#define IF_EQ_1(a, b) IF_EQ_2(a, b)
#define IF_EQ_2(a, b) IF_EQ_##a##_##b

#define IF_EQ_$_$    TRUE_
#define TRUE_       *

// 测试用例
//CONVERT_DOLLAR_TO_STAR($)   // 展开为 *
//CONVERT_DOLLAR_TO_STAR(a)   // 展开为 a
//CONVERT_DOLLAR_TO_STAR(*)   // 展开为 *

// 辅助宏：拼接两个标记
#define PRIMITIVE_CAT(a, b) a##_##b
#define CAT(a, b) PRIMITIVE_CAT(a, b)

// 计算变参个数（支持1~5个参数）
#define COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) COUNT_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)

// 根据参数数量调用对应的处理宏
#define SNAKE_CASE_1(a) a
#define SNAKE_CASE_2(a, ...) CAT(a, SNAKE_CASE_1(__VA_ARGS__))
#define SNAKE_CASE_3(a, ...) CAT(a, SNAKE_CASE_2(__VA_ARGS__))
#define SNAKE_CASE_4(a, ...) CAT(a, SNAKE_CASE_3(__VA_ARGS__))
#define SNAKE_CASE_5(a, ...) CAT(a, SNAKE_CASE_4(__VA_ARGS__))

// 主宏：将参数拼接为蛇形命名
#define SNAKE_CASE(...) \
    CAT(SNAKE_CASE, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

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
//VA_ARG2STR(const, struct, typeInfo, *)
//"const struct typeInfo *"
#define $ *
//VA_ARG2TYPE(const, struct, typeInfo, $)
//const struct typeInfo *

static const typeInfo typeInfo_fieldTypeId = {
    "fieldTypeId", sizeof(fieldTypeId), sizeof(fieldTypeId), 0, NULL, 0,
};

static const typeInfo typeInfo_const_struct_typeInfo_$ = {
    "const struct typeInfo *", sizeof(const struct typeInfo *), sizeof(const struct typeInfo *), 0, NULL, 0,
};

static const typeInfo typeInfo_const_char_$ = {
    "const char *", sizeof(const char *), sizeof(const char *), 0, NULL, 0,
};

static const typeInfo typeInfo_size_t = {
    "size_t", sizeof(size_t), sizeof(size_t), 0, NULL, 0,
};

static const fieldInfo fields_fieldInfo[] = {
    {fieldTypeId_Enum, &typeInfo_fieldTypeId, "id", offsetof(fieldInfo, id), 0},
    {fieldTypeId_Ptr, &typeInfo_const_struct_typeInfo_$, "type", offsetof(fieldInfo, type), 0},
    {fieldTypeId_Ptr, &typeInfo_const_char_$, "name", offsetof(fieldInfo, name), 0},
    {fieldTypeId_Int, &typeInfo_size_t, "offset", offsetof(fieldInfo, offset), 0},
    {fieldTypeId_Int, &typeInfo_size_t, "length", offsetof(fieldInfo, length), 0},
};

static const typeInfo typeInfo_fieldInfo = {
    "fieldInfo", sizeof(fieldInfo), sizeof(fieldInfo), ARRAY_SIZE(fields_fieldInfo), fields_fieldInfo, 0,
};

static const typeInfo typeInfo_const_fieldInfo_$ = {
    "const fieldInfo *", sizeof(const fieldInfo *), sizeof(const fieldInfo *), 0, NULL, 0,
};

static const typeInfo typeInfo_bool = {
    "bool", sizeof(bool), sizeof(bool), 0, NULL, 0,
};

static const fieldInfo fields_typeInfo[] = {
    {fieldTypeId_Ptr, &typeInfo_const_char_$, "name", offsetof(typeInfo, name), 0},
    {fieldTypeId_Int, &typeInfo_size_t, "size", offsetof(typeInfo, size), 0},
    {fieldTypeId_Int, &typeInfo_size_t, "sizePacked", offsetof(typeInfo, sizePacked), 0},
    {fieldTypeId_Int, &typeInfo_size_t, "fieldsLength", offsetof(typeInfo, fieldsLength), 0},
    {fieldTypeId_Ptr, &typeInfo_const_fieldInfo_$, "fields", offsetof(typeInfo, fields), 0},
    {fieldTypeId_Bool, &typeInfo_bool, "isSigned", offsetof(typeInfo, isSigned), 0},
};

static const typeInfo typeInfo_typeInfo = {
    "typeInfo", sizeof(typeInfo), sizeof(typeInfo), ARRAY_SIZE(fields_typeInfo), fields_typeInfo, 0,
};

int main() {
    system("chcp 65001");
    clock_t start = clock();

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
