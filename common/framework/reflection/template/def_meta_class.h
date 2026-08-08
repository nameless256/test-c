#include "mcr_util.h"
#include "meta.h"

#ifndef className
#error "className is not defined"
#endif

#ifndef classBaseName
#define classBaseName objBase
#endif

#define classMetaName cat_2(className, meta)
#define classMetaFieldsName cat_2(classMetaName, fields)

#ifndef _classFieldDef
#define __classFieldDef2(_field, _dsc) \
{ .base = { .dsc = name2Str(_dsc), .name = name2Str(_field), }, .ofs = offsetof(className, _field), },
#define __classFieldDef3(_field, _dsc, _bits) \
{ .base = { .dsc = name2Str(_dsc: _bits), .name = name2Str(_field), }, .bits = _bits, },
#define _classFieldDef(...) cat2(__classFieldDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#endif

#ifdef classMember
static const meta_field classMetaFieldsName[] = {
    classMember(_classFieldDef)
};
#endif

#if classBaseName != objBase
extern const meta_type cat_2(classBaseName, meta);
#endif

registerMetaType(classMetaName) = {
    .mClass = {
        .base = {
            .name = nameVal2Str(className),
            .size = sizeof(className),
            .quals = qual_Null,
            .id = typeId_Class,
        },
#if classBaseName != objBase
        .baseClass = (const meta_class *) &cat_2(classBaseName, meta),
#endif
#ifdef classMember
        .cnt = ARRAY_SIZE(classMetaFieldsName),
        .fields = classMetaFieldsName,
#endif
        .ctor = (void *) cat_2(className, ctor),
        .dtor = (void *) cat_2(className, dtor),
        .copy = (void *) cat_2(className, copy),
    }
};

#undef classMetaFieldsName
#undef classMetaName
#undef className
#undef classBase
#undef classMember
#undef classBaseName
