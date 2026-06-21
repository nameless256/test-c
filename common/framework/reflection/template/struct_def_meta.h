#include "mcr_util.h"
#include "type_meta.h"

#ifndef structName
#error "structName is not defined"
#endif

#ifndef structMember
#error "structMember is not defined"
#endif

#define structMetaName cat_2(structName, meta)
#define structMetaFieldsName cat_2(structMetaName, fields)

#ifndef _structFieldDef
#define __structFieldDef2(_field, _dsc) \
    { \
        .base = { .dsc = { .str = name2Str(_dsc) }, .name = name2Str(_field), }, \
        .ofs = structOfsOf(structName, _field), \
    },
#define _structFieldDef(...) cat2(__structFieldDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#endif

static const fieldMeta structMetaFieldsName[] = {
    structMember(_structFieldDef)
};

const structMeta structMetaName = {
    .base = {
        .name = name2Str(structName),
        .size = sizeof(structName),
        .quals = qual_Null,
        .id = typeId_Struct,
    },
    .cnt = ARRAY_SIZE(structMetaFieldsName),
    .fields = structMetaFieldsName,
};

#undef structMetaFieldsName
#undef structMetaName
#undef structName
#undef structBase
#undef structMember
