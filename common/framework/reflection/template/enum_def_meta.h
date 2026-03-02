#include "mcr_util.h"
#include "type_meta.h"

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

static const char *enumMetaFunc(name)(void) {
    return name2Str(enumName);
}

static size_t enumMetaFunc(size)(void) {
    return sizeof(enumBase);
}

static qual enumMetaFunc(quals)(void) {
    return qual_Null;
}

static typeId enumMetaFunc(id)(void) {
    return typeId_Enum;
}

static size_t enumMetaFunc(cnt)(void) {
    return mcrVaCount(enumMember);
}

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

const enumMeta enumMetaName = {
    .base = {
        .name = enumMetaFunc(name),
        .size = enumMetaFunc(size),
        .quals = enumMetaFunc(quals),
        .id = enumMetaFunc(id),
    },
    .type = &cat_2(enumBase, meta),
    .cnt = enumMetaFunc(cnt),
};

#undef enumMetaName
#undef enumMetaFunc
#undef enumName
#undef enumBase
#undef enumMember
