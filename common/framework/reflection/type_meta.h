//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>

typedef union typeMeta typeMeta;
typedef struct enumMeta enumMeta;

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

#include "enum_def.h"

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

#include "enum_def.h"

typedef struct typeMetaBase typeMetaBase;

struct typeMetaBase {
    const char *name;
    size_t size;
    qual quals;
    typeId id;
};

typedef struct intMeta intMeta;

struct intMeta {
    typeMetaBase base;
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

#include "enum_def.h"

typedef struct paramMeta paramMeta;

typedef struct funcMeta funcMeta;

typedef struct arrayMeta arrayMeta;

struct arrayMeta {
    typeMetaBase base;
    const typeMeta *type;
    size_t length;
};

typedef struct ptrMeta ptrMeta;

struct ptrMeta {
    typeMetaBase base; ///< base.name == "*"
    ptrTypeId id;
    union {
        typeMeta *type;
        funcMeta *func;
        arrayMeta *array;
    };
};

typedef struct enumValMeta enumValMeta;

struct enumValMeta {
    const char *name;
    int value;
};

struct enumMeta {
    typeMetaBase base;
    const intMeta *type;
    size_t cnt;
    const enumValMeta *const vals;
};

typedef struct fieldMeta fieldMeta;

typedef struct unionMeta unionMeta;

struct unionMeta {
    typeMetaBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const fieldMeta *const fields;
};

typedef struct structMeta structMeta;

struct structMeta {
    typeMetaBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const fieldMeta *const fields;
};

typedef struct objBase objBase;

typedef struct classMeta classMeta;

struct classMeta {
    typeMetaBase base;
    classMeta *baseClass;
    size_t cnt;
    const fieldMeta *const fields;
    bool (*ctor)(objBase *);
    void (*dtor)(objBase *);
    bool (*copy)(objBase *, objBase *);
};

struct objBase {
    classMeta *class;
};

union typeMeta {
    typeMetaBase base;
    intMeta intMeta;
    ptrMeta ptrMeta;
    enumMeta enumMeta;
    arrayMeta arrayMeta;
    unionMeta unionMeta;
    structMeta structMeta;
    classMeta classMeta;
};

typedef struct paramTypeDsc paramTypeDsc;

struct paramTypeDsc {
    const char *str;
    const typeMeta *ptr;
};

struct paramMeta {
    union {
        paramTypeDsc dsc;
        const typeMeta type;
    };
    const char *name;
    bool parsed;
};

struct fieldMeta {
    paramMeta base;
    size_t ofs;
    /// VvV It is useless and has high implementation complexity, so no support is provided
    // uint8_t bitCnt;
    // uint8_t bitOfs;
};

struct funcMeta {
    const paramMeta retType; ///< return type; type->name == func name
    const paramMeta *const params;
    bool isVarArgs;
    uint8_t cnt; ///< isVarArgs == true, e.g. printf(fmt, ...) cnt == 1
};

void obj_dtor(objBase *obj);
bool obj_ctor(objBase *obj);
bool obj_copy(objBase *restrict obj, objBase *restrict other);

#define intMetaDeclare(name) extern const intMeta cat_2(name, meta)
intMetaDeclare(int8_t);
intMetaDeclare(uint8_t);
intMetaDeclare(int16_t);
intMetaDeclare(uint16_t);
intMetaDeclare(int32_t);
intMetaDeclare(uint32_t);
intMetaDeclare(int64_t);
intMetaDeclare(uint64_t);
intMetaDeclare(size_t);

#define baseTypeMetaDeclare(name) extern const typeMetaBase cat_2(name, meta)
baseTypeMetaDeclare(bool);
baseTypeMetaDeclare(float);
baseTypeMetaDeclare(double);

#ifdef TYPE_META_H_IMPL
#define intName int8_t
#include "int_def_meta.h"
#define intName uint8_t
#include "int_def_meta.h"
#define intName int16_t
#include "int_def_meta.h"
#define intName uint16_t
#include "int_def_meta.h"
#define intName int32_t
#include "int_def_meta.h"
#define intName uint32_t
#include "int_def_meta.h"
#define intName int64_t
#include "int_def_meta.h"
#define intName uint64_t
#include "int_def_meta.h"
#define intName size_t
#include "int_def_meta.h"

#define baseTypeName bool
#define baseTypeId typeId_Bool
#include "base_type_def_meta.h"

#define baseTypeName float
#define baseTypeId typeId_Float
#include "base_type_def_meta.h"

#define baseTypeName double
#define baseTypeId typeId_Float
#include "base_type_def_meta.h"

#define enumName _typeId_enumName
#define enumBase _typeId_enumBase
#define enumMember(f) _typeId_enumMember(f)
#include "enum_def_meta.h"

#define enumName _qual_enumName
#define enumBase _qual_enumBase
#define enumMember(f) _qual_enumMember(f)
#include "enum_def_meta.h"

#define enumName _ptrTypeId_enumName
#define enumBase _ptrTypeId_enumBase
#define enumMember(f) _ptrTypeId_enumMember(f)
#include "enum_def_meta.h"
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

#ifdef TYPE_META_H_IMPL
#undef TYPE_META_H_IMPL
#endif

#endif //TYPE_META_H
