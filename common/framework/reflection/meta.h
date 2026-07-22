//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>
#include "mcr_util.h"

typedef union meta_type meta_type;
typedef struct meta_enum meta_enum;

#define _typeId_enumName typeId
#define _typeId_enumBase uint8_t
#define _typeId_enumMember(f) \
mcrDispatch(f, Bool) \
mcrDispatch(f, Int) \
mcrDispatch(f, Ptr) \
mcrDispatch(f, Enum) \
mcrDispatch(f, Float) \
mcrDispatch(f, Array) \
mcrDispatch(f, Union) \
mcrDispatch(f, Struct) \
mcrDispatch(f, Class)

#define enumName _typeId_enumName
#define enumBase _typeId_enumBase
#define enumMember(f) _typeId_enumMember(f)

#include "def_enum.h"

#define _qual_enumName qual
#define _qual_enumBase uint8_t
#define _qual_enumMember(f) \
mcrDispatch(f, Null, 0b000) \
mcrDispatch(f, Const, 0b001) \
mcrDispatch(f, Volatile, 0b010) \
mcrDispatch(f, Restrict, 0b100)

#define enumName _qual_enumName
#define enumBase _qual_enumBase
#define enumMember(f) _qual_enumMember(f)

#include "def_enum.h"

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

#define _ptrTypeId_enumName ptrTypeId
#define _ptrTypeId_enumBase uint8_t
#define _ptrTypeId_enumMember(f) \
mcrDispatch(f, Type) \
mcrDispatch(f, Func) \
mcrDispatch(f, Array)

#define enumName _ptrTypeId_enumName
#define enumBase _ptrTypeId_enumBase
#define enumMember(f) _ptrTypeId_enumMember(f)

#include "def_enum.h"

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

typedef struct meta_class meta_class;

struct meta_class {
    meta_typeBase base;
    meta_class *baseClass;
    size_t cnt;
    const meta_field *const fields;
    bool (*ctor)(objBase *);
    void (*dtor)(objBase *);
    bool (*copy)(objBase *, objBase *);
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
    meta_type type;
    const char *name;
    const char *dsc;
};

struct meta_field {
    meta_param base;
    size_t ofs;
    /// VvV It is useless and has high implementation complexity, so no support is provided
    // uint8_t bitCnt;
    // uint8_t bitOfs;
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

extern meta_type __meta_type_data_start;
extern meta_type __meta_type_data_end;

#define registerMetaType(type) SECTION(".meta_type_data") const meta_type type
#define foreachMetaType(i) for (meta_type *i = &__meta_type_data_start; i < &__meta_type_data_end; ++i)

#ifdef TYPE_META_H_IMPL
#define enumName _typeId_enumName
#define enumBase _typeId_enumBase
#define enumMember(f) _typeId_enumMember(f)
#include "def_meta_enum.h"

#define enumName _qual_enumName
#define enumBase _qual_enumBase
#define enumMember(f) _qual_enumMember(f)
#include "def_meta_enum.h"

#define enumName _ptrTypeId_enumName
#define enumBase _ptrTypeId_enumBase
#define enumMember(f) _ptrTypeId_enumMember(f)
#include "def_meta_enum.h"
#undef TYPE_META_H_IMPL
#endif

#undef _typeId_enumName
#undef _typeId_enumBase
#undef _typeId_enumMember
#undef _qual_enumName
#undef _qual_enumBase
#undef _qual_enumMember
#undef _ptrTypeId_enumName
#undef _ptrTypeId_enumBase
#undef _ptrTypeId_enumMember

#endif //TYPE_META_H
