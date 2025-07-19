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

/**
 * @defgroup Main
 * @{
 */

#define sumDef(type) type sum_##type(type arg0, type arg1)
#define sumDefBase(type) type sum_##type(type arg0, type arg1) { return arg0 + arg1; }
#define sum(type) sum_##type

sumDefBase(double)

sumDefBase(int)

#define enumValDefDefault(name) name,
#define enumValDefInit(name, default) name = default,
#define enumValCapture(name) case name: return name2Str(name);
#define enumIter(name) enumIter ## _ ## name
#define enumDispatch(f, n) f(n)

#define enumDef(name) typedef enum { enumIter(name)(enumValDefDefault) } (name);
#define enumDefToStr(name) \
static inline char *name ## _ ## toStr(name val) { \
    switch(val) { enumIter(name)(enumValCapture) default: return "NaN"; } \
};

#define enumIter_fieldTypeId(action) \
action(fieldTypeId_Integer) \
action(fieldTypeId_Float) \
action(fieldTypeId_Pointer) \
action(fieldTypeId_Array)

enumDef(fieldTypeId)
enumDefToStr(fieldTypeId)

typedef struct {
    const char *name;
    fieldTypeId id;
} fieldTypeInfo;

typedef struct {
    fieldTypeInfo type;
    const char *name;
    size_t size;
    size_t offset;
    size_t length;
    bool isSigned;
} fieldInfo;

struct _MKCREFLECT_TypeInfo {
    const char *name;
    size_t fields_count;
    size_t size;
    size_t packed_size;
    fieldInfo *fields;
};

typedef struct {
    double f;
    int i;
} testStruct;

sumDef(testStruct) {
    return (testStruct) {sum(double)(arg0.f, arg1.f), sum(int)(arg0.i, arg1.i)};
}

int main() {
    system("chcp 65001");
    clock_t start = clock();

//    oopHeapUsage();
//    oopUsage();
    printf("[%d] --------- {%s} %d %f \n", __LINE__, __FUNCTION__, sum(int)(6, 9), sum(double)(3.14, 2.96));

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
//    system("pause");
    return 0;
}

/** @} */
