//
// Created by xiaoxianghui on 2025/9/8.
//

#ifndef TEST_C_ENUM_DEF_H
#define TEST_C_ENUM_DEF_H

#include "type_meta.h"
#include "mcr_util.h"

#define __enumPrefValDef1(pref, tuple) cat_2(pref, vaTuple(tuple, 0))
#define __enumPrefValDef0(pref, tuple) (__enumPrefValDef1(pref, tuple), vaTuple(tuple, 1))
#define _enumPrefValDef(pref, tuple) cat2(__enumPrefValDef, vaTupleArgCountEq1(tuple)) (pref, tuple)

#define __enumValDef1(tuple) vaTuple(tuple, 0),
#define __enumValDef0(tuple) vaTuple(tuple, 0) = vaTuple(tuple, 1),
#define _enumValDef(tuple) cat2(__enumValDef, vaTupleArgCountEq1(tuple)) (tuple)

#define __enumTupleDefBase1(tuple) (vaTuple(tuple, 0), int)
#define __enumTupleDefBase0(tuple) tuple
#define _enumTupleDefBase(tuple) cat2(__enumTupleDefBase, vaTupleArgCountEq1(tuple)) (tuple)

#define enumDef(tuple, ...) \
_enumDef(_enumTupleDefBase(tuple), mcrParamPIter(_enumPrefValDef, asIs, vaTuple(tuple, 0), __VA_ARGS__))
#define _enumDef(tuple, ...) \
typedef vaTuple(tuple, 1) vaTuple(tuple, 0); \
enum cat2(_, vaTuple(tuple, 0)){ \
mcrIter(_enumValDef, __VA_ARGS__) \
}

#endif //TEST_C_ENUM_DEF_H
