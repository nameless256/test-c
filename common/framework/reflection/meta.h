//
// Created by Admin on 25-10-19.
//

#ifndef META_H
#define META_H

#include <stdbool.h>
#include <stdint.h>
#include "mcr_util.h"

#define _enumValDef1(name) cat_2(enumName, name),
#define _enumValDef2(name, value) cat_2(enumName, name) = value,
#define enumValDef(...) cat2(_enumValDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#define enumValMetaDef(name, ...) {nameVal2Str(name), cat_2(enumName, name)},
#define _classFieldDef3(dsc, name, bits) dsc: bits;
#define _classFieldDef2(dsc, name) dsc;
#define classFieldDef(...) cat2(_classFieldDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#define _classFieldMetaDef2(_dsc, _field) \
{ .base = { .dsc = name2Str(_dsc), .name = name2Str(_field), }, .ofs = offsetof(className, _field), },
#define _classFieldMetaDef3(_dsc, _field, _bits) \
{ .base = { .dsc = name2Str(_dsc: _bits), .name = name2Str(_field), }, .bits = _bits, },
#define classFieldMetaDef(...) cat2(_classFieldMetaDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)

typedef union meta_type meta_type;
typedef struct meta_enum meta_enum;

#include "def_enum.h"
#include "enum_typeId.h"

#include "def_enum.h"
#include "enum_qual.h"

typedef struct meta_typeBase meta_typeBase;

struct meta_typeBase {
    const char *name;
    size_t size;
    qual quals;
    typeId id;
};

typedef struct meta_int meta_int;

struct meta_int {
    meta_typeBase base;
    bool isSigned;
};

#include "def_enum.h"
#include "enum_ptrTypeId.h"

typedef struct meta_param meta_param;

typedef struct meta_func meta_func;

typedef struct meta_array meta_array;

struct meta_array {
    meta_typeBase base;
    const meta_type *type;
    size_t length;
};

typedef struct meta_ptr meta_ptr;

struct meta_ptr {
    meta_typeBase base; ///< base.name == "*"
    ptrTypeId id;
    union {
        meta_type *type;
        meta_func *func;
        meta_array *array;
    };
};

typedef struct meta_enumVal meta_enumVal;

struct meta_enumVal {
    const char *name;
    int value;
};

struct meta_enum {
    meta_typeBase base;
    const meta_type *type;
    size_t cnt;
    const meta_enumVal *const vals;
};

typedef struct meta_field meta_field;

typedef struct meta_union meta_union;

struct meta_union {
    meta_typeBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const meta_field *const fields;
};

typedef struct meta_struct meta_struct;

struct meta_struct {
    meta_typeBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const meta_field *const fields;
};

typedef struct objBase objBase;

typedef bool (*if_ctor)(objBase *);
typedef void (*if_dtor)(objBase *);
typedef bool (*if_copy)(objBase *, objBase *);

typedef struct if_specMethod if_specMethod;
struct if_specMethod {
    if_ctor ctor;
    if_dtor dtor;
    if_copy copy;
};

#define export(ret, func, ...) \
ret cat_2(className, func)(className *self, ##__VA_ARGS__)

#define method(ret, func, ...) \
ret func(className *self, ##__VA_ARGS__) __attribute__((alias(nameVal2Str(cat_2(className, func))))); \
ret cat_2(className, func)(className *self, ##__VA_ARGS__)

#define virtual(ret, func, ...) ret (*func)(className *self, ##__VA_ARGS__)

// private
// protected
// public

#define bind(name) .name = name

#define classVtab \
typedef struct cat_2(className, vtab) cat_2(className, vtab); \
struct cat_2(className, vtab) { \
    virtual(bool, ctor); \
    virtual(void, dtor); \
    virtual(bool, copy, className *other); \
}; \
static const cat_2(className, vtab) vtab

typedef struct meta_class meta_class;

struct meta_class {
    meta_typeBase base;
    const meta_class *baseClass;
    size_t cnt;
    const meta_field *fields;
    const void *vptr;
};

struct objBase {
    meta_class *class;
};

union meta_type {
    meta_typeBase base;
    meta_int mInt;
    meta_ptr mPtr;
    meta_enum mEnum;
    meta_array mArray;
    meta_union mUnion;
    meta_struct mStruct;
    meta_class mClass;
};

struct meta_param {
    const char *name;
    const char *dsc;
};

struct meta_field {
    meta_param base;
    size_t ofs;
    uint8_t bits;
};

struct meta_func {
    const meta_param retType; ///< return type; type->name == func name
    const meta_param *const params;
    bool isVarArgs;
    uint8_t cnt; ///< isVarArgs == true, e.g. printf(fmt, ...) cnt == 1
};

#define metaTypeDecl(name) extern const meta_type cat_2(name, meta)
metaTypeDecl(int8_t);
metaTypeDecl(uint8_t);
metaTypeDecl(int16_t);
metaTypeDecl(uint16_t);
metaTypeDecl(int32_t);
metaTypeDecl(uint32_t);
metaTypeDecl(int64_t);
metaTypeDecl(uint64_t);
metaTypeDecl(size_t);
metaTypeDecl(char);
metaTypeDecl(bool);
metaTypeDecl(float);
metaTypeDecl(double);

extern meta_type __start_meta_type_data;
extern meta_type __stop_meta_type_data;

#define registerMetaType(type) __attribute__((section("meta_type_data"), aligned(4))) const meta_type type
#define foreachMetaType(i) for (meta_type *i = &__start_meta_type_data; i < &__stop_meta_type_data; ++i)

#endif //META_H
