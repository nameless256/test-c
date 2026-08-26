//
// Created by CodingDev on 2026/8/26.
//
#include "meta.h"

#define enumStart static meta_enumVal cat_2(enumName, vals)[] = {

#define enumEntry(...) enumValMetaDef(__VA_ARGS__)

#define enumEnd }; \
extern const meta_type cat_2(enumBase, meta); \
registerMetaType(cat_2(enumName, meta)) = { \
    .mEnum = { \
        .base = { \
            .name = nameVal2Str(enumName), \
            .size = sizeof(enumBase), \
            .quals = qual_Null, \
            .id = typeId_Enum, \
        }, \
        .type = &cat_2(enumBase, meta), \
        .cnt = ARRAY_SIZE(cat_2(enumName, vals)), \
        .vals = cat_2(enumName, vals), \
    } \
};
