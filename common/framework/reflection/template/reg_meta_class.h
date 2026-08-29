//
// Created by CodingDev on 2026/8/28.
//
#include "meta.h"

#define classStart \
static const meta_field fields[] = { \
    classEntry(classBase base, base)

#define classEntry(...) classFieldMetaDef(__VA_ARGS__)

#define classEnd \
}; \
extern const meta_type cat_2(classBase, meta); \
registerMetaType(cat_2(className, meta)) = { \
    .mClass = { \
        .base = { \
            .name = nameVal2Str(className), \
            .size = sizeof(className), \
            .quals = qual_Null, \
            .id = typeId_Class, \
        }, \
        .baseClass = (const meta_class *) &cat_2(classBase, meta), \
        .cnt = ARRAY_SIZE(fields), \
        .fields = fields, \
        .vptr = &vtab \
    } \
};
