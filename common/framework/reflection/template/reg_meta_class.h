//
// Created by CodingDev on 2026/8/28.
//
#include "meta.h"

#define classStart \
static const meta_field cat_2(className, fields)[] = { \
    classEntry(classBase base, base)

#define classEntry(...) classFieldDef(__VA_ARGS__)

/// 0xOil: \todo 特殊成员函数vtab重构
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
        .cnt = ARRAY_SIZE(cat_2(className, fields)), \
        .fields = cat_2(className, fields), \
    } \
};
