//
// Created by xiaoxianghui on 2025/9/8.
//

#ifndef TEST_C_ENUM_DEF_H
#define TEST_C_ENUM_DEF_H

#include "type_meta.h"
#include "mcr_util.h"

#define __enumPrefValDef1(pref, tuple) cat_2(pref, mcrVaTuple(tuple, 0))
#define __enumPrefValDef0(pref, tuple) (__enumPrefValDef1(pref, tuple), mcrVaTuple(tuple, 1))
#define _enumPrefValDef(pref, tuple) cat2(__enumPrefValDef, mcrVaTupleArgCountEq1(tuple)) (pref, tuple)

#define __enumValDef1(tuple) mcrVaTuple(tuple, 0),
#define __enumValDef0(tuple) mcrVaTuple(tuple, 0) = mcrVaTuple(tuple, 1),
#define _enumValDef(tuple) cat2(__enumValDef, mcrVaTupleArgCountEq1(tuple)) (tuple)

#define __enumTupleDefBase1(tuple) (mcrVaTuple(tuple, 0), int)
#define __enumTupleDefBase0(tuple) tuple
#define _enumTupleDefBase(tuple) cat2(__enumTupleDefBase, mcrVaTupleArgCountEq1(tuple)) (tuple)

#define enumDef(tuple, ...) \
_enumDef(_enumTupleDefBase(tuple), mcrParamPIter(_enumPrefValDef, asIs, mcrVaTuple(tuple, 0), __VA_ARGS__))
#define _enumDef(tuple, ...) \
typedef mcrVaTuple(tuple, 1) mcrVaTuple(tuple, 0); \
enum cat2(_, mcrVaTuple(tuple, 0)){ \
mcrIter(_enumValDef, __VA_ARGS__) \
}

const intMeta intMeta_uint8_t = {
    .base = {.name = "uint8_t", .size = sizeof(uint8_t), .quals = qual_Null, .id = typeId_Int},
};

enumDef((temp, uint8_t), 2, (3), (5, 9));

typedef struct _enumValMeta_temp enumValMeta_temp;
struct _enumValMeta_temp {
    enumValMetaBase base;
    uint8_t value;
};

const enumValMeta_temp enumValMeta_temp_2 = {.base = {.name = "temp_2", .idx = 0}, .value = temp_2};
const enumValMeta_temp enumValMeta_temp_3 = {.base = {.name = "temp_3", .idx = 1}, .value = temp_3};
const enumValMeta_temp enumValMeta_temp_5 = {.base = {.name = "temp_5", .idx = 2}, .value = temp_5};

const enumValMetaBase *const enumValMeta_temp_tab[] = {
    (const enumValMetaBase *) &enumValMeta_temp_2,
    (const enumValMetaBase *) &enumValMeta_temp_3,
    (const enumValMetaBase *) &enumValMeta_temp_5,
};

const enumMeta enumMeta_temp = {
    .base = {.name = "temp", .size = sizeof(temp), .quals = qual_Null, .id = typeId_Enum},
    .type = (typeMetaBase *) &intMeta_uint8_t,
    .cnt = 3,
    .tab = enumValMeta_temp_tab,
};

#endif //TEST_C_ENUM_DEF_H
