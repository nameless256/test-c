#include "mcr_util.h"
#include "meta.h"

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
#define enumMetaValsName cat_2(enumMetaName, vals)

extern const meta_type cat_2(enumBase, meta);

#ifndef _enumValMetaDef
#define _enumValMetaDef(name, ...) {nameVal2Str(name), cat_2(enumName, name)},
#endif

static meta_enumVal enumMetaValsName[] = {
    enumMember(_enumValMetaDef)
};

registerMetaType(enumMetaName) = {
    .mEnum = {
        .base = {
            .name = nameVal2Str(enumName),
            .size = sizeof(enumBase),
            .quals = qual_Null,
            .id = typeId_Enum,
        },
        .type = &cat_2(enumBase, meta),
        .cnt = ARRAY_SIZE(enumMetaValsName),
        .vals = enumMetaValsName,
    }
};

#undef enumMetaValsName
#undef enumMetaName
#undef enumName
#undef enumBase
#undef enumMember
