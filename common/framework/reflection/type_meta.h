//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>

typedef struct typeMeta typeMeta;
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

typedef struct ptrMetaBase ptrMetaBase;
struct ptrMetaBase {
    typeMetaBase base; ///< base.name == "*"
    ptrTypeId id;
};

typedef struct typePtrMeta typePtrMeta;
struct typePtrMeta {
    ptrMetaBase base;
    const typeMeta *type;
};

typedef struct paramMeta paramMeta;
struct paramMeta {
    const typeMeta *type;
    const char *name;
};

typedef struct funcMeta funcMeta;
struct funcMeta {
    const typeMeta *type; ///< return type
    bool isVarArgs;
    uint8_t cnt; ///< isVarArgs == true, e.g. printf(fmt, ...) funcMeta::cnt == 1
    const paramMeta *const *params;
};

typedef struct funcPtrMeta funcPtrMeta;
struct funcPtrMeta {
    ptrMetaBase base;
    funcMeta *func;
};

typedef struct arrayMeta arrayMeta;
struct arrayMeta {
    typeMetaBase base;
    const typeMeta *type;
    size_t length;
};

typedef struct arrayPtrMeta arrayPtrMeta;
struct arrayPtrMeta {
    ptrMetaBase base;
    arrayMeta *array;
};

typedef struct ptrMeta ptrMeta;
struct ptrMeta {
    union {
        ptrMetaBase base;
        typePtrMeta type;
        funcPtrMeta func;
        arrayPtrMeta array;
    };
};

struct enumMeta {
    typeMetaBase base;
    const intMeta *type;
    size_t cnt;
    int (*getIdxByValue)(int64_t value);
    int (*getIdxByName)(const char *name);
    int64_t (*getValueByIdx)(int idx);
    int64_t (*getValueByName)(const char *name);
    const char *(*getNameByIdx)(int idx);
    const char *(*getNameByValue)(int64_t value);
};

#ifdef TYPE_META_H_IMPL
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

typedef struct fieldMetaBase fieldMetaBase;
struct fieldMetaBase {
    paramMeta base;
    size_t ofs;
    bool isBitField;
};

typedef struct bitFieldMeta bitFieldMeta;
struct bitFieldMeta {
    fieldMetaBase base;
    uint8_t cnt;
    uint8_t ofs;
};

typedef struct fieldMeta fieldMeta;
struct fieldMeta {
    union {
        fieldMetaBase base;
        bitFieldMeta bitField;
    };
};

typedef struct unionMeta unionMeta;
struct unionMeta {
    typeMetaBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const fieldMeta *const *fields;
};

typedef struct structMeta structMeta;
struct structMeta {
    typeMetaBase base; ///< if not define name, base.name == <anonymous>
    size_t cnt;
    const fieldMeta *const *fields;
};

typedef struct objBase objBase;

typedef struct classMeta classMeta;
struct classMeta {
    typeMetaBase base;
    classMeta *baseClass;
    size_t cnt;
    const fieldMeta *const *fields;
    bool (*ctor)(objBase *);
    void (*dtor)(objBase *);
    bool (*copy)(objBase *, objBase *);
};

struct objBase {
    classMeta *class;
};

struct typeMeta {
    union {
        typeMetaBase base;
        intMeta intMeta;
        ptrMeta ptrMeta;
        enumMeta enumMeta;
        arrayMeta arrayMeta;
        unionMeta unionMeta;
        structMeta structMeta;
        classMeta classMeta;
    };
};

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
#endif

#ifdef TYPE_META_H_IMPL
#undef TYPE_META_H_IMPL
#endif

#endif //TYPE_META_H
