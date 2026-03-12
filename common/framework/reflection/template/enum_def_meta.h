#include "mcr_util.h"
#include "type_meta.h"

#include <string.h>

#ifndef enumName
#error "enumName is not defined"
#endif

#ifndef enumBase
#define enumBase int
#endif

#ifndef enumMember
#error "enumMember is not defined"
#endif

#define enumMetaName cat_2(enumName, meta)
#define enumMetaFunc(name) cat_2(enumMetaName, name)

extern const intMeta cat_2(enumBase, meta);

#ifndef _enumValMetaDef
#define _enumValMetaDef(tuple) {nameVal2Str(mcrVaTuple(tuple, 0)), cat_2(enumName, mcrVaTuple(tuple, 0))},
#endif

struct {
    const char *name;
    enumBase value;
} static cat_2(enumMetaName, tab)[] = {
    mcrIter(_enumValMetaDef, enumMember)
};

static int enumMetaFunc(getIdxByValue) (int64_t value) {
    for (int i = 0; i < ARRAY_SIZE(cat_2(enumMetaName, tab)); i++) {
        if (cat_2(enumMetaName, tab)[i].value == value) return i;
    }
    return -1;
}

static int enumMetaFunc(getIdxByName) (const char *name) {
    for (int i = 0; i < ARRAY_SIZE(cat_2(enumMetaName, tab)); i++) {
        if (strcmp(cat_2(enumMetaName, tab)[i].name, name) == 0) return i;
    }
    return -1;
}

static int64_t enumMetaFunc(getValueByIdx) (int idx) {
    if (idx < 0 || ARRAY_SIZE(cat_2(enumMetaName, tab)) <= idx) return INT64_MIN;
    return cat_2(enumMetaName, tab)[idx].value;
}

static int64_t enumMetaFunc(getValueByName) (const char *name) {
    int idx = enumMetaFunc(getIdxByName)(name);
    if (idx < 0) return INT64_MIN;
    return cat_2(enumMetaName, tab)[idx].value;
}

static const char *enumMetaFunc(getNameByIdx) (int idx) {
    if (idx < 0 || ARRAY_SIZE(cat_2(enumMetaName, tab)) <= idx) return 0;
    return cat_2(enumMetaName, tab)[idx].name;
}

static const char *enumMetaFunc(getNameByValue) (int64_t value) {
    int idx = enumMetaFunc(getIdxByValue)(value);
    if (idx < 0) return NULL;
    return cat_2(enumMetaName, tab)[idx].name;
}

const enumMeta enumMetaName = {
    .base = {
        .name = name2Str(enumName),
        .size = sizeof(enumBase),
        .quals = qual_Null,
        .id = typeId_Enum,
    },
    .type = &cat_2(enumBase, meta),
    .cnt = mcrVaCount(enumMember),
    .getIdxByValue = enumMetaFunc(getIdxByValue),
    .getIdxByName = enumMetaFunc(getIdxByName),
    .getValueByIdx = enumMetaFunc(getValueByIdx),
    .getValueByName = enumMetaFunc(getValueByName),
    .getNameByIdx = enumMetaFunc(getNameByIdx),
    .getNameByValue = enumMetaFunc(getNameByValue),
};

#undef enumMetaName
#undef enumMetaFunc
#undef enumName
#undef enumBase
#undef enumMember
