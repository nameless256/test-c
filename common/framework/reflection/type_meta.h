//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>

typedef struct typeMeta typeMeta;
typedef struct enumMeta enumMeta;

#define enumName typeId
#define enumBase uint8_t
#define enumMember Bool, Int, Ptr, Enum, Float, Array, Union, Struct,

#include "enum_def.h"

#define enumName qual
#define enumBase uint8_t
#define enumMember (Null, 0b000), (Const, 0b001), (Volatile, 0b010), (Restrict, 0b100),

#include "enum_def.h"

typedef struct typeMetaBase typeMetaBase;
struct typeMetaBase {
    const char *(*name)(void);
    size_t (*size)(void);
    qual (*quals)(void);
    typeId (*id)(void);
};

typedef struct intMeta intMeta;
struct intMeta {
    typeMetaBase base;
    bool (*isSigned)(void);
};

#define enumName ptrTypeId
#define enumBase uint8_t
#define enumMember Type, Func, Array

#include "enum_def.h"

typedef struct ptrMetaBase ptrMetaBase;
struct ptrMetaBase {
    typeMetaBase base;
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
    const typeMeta *type;
    bool isVarArgs;
    uint8_t cnt;
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
    size_t (*cnt)(void);
    // const enumValMetaBase *const *tab;
};

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
    typeMetaBase base;
    size_t cnt;
    const fieldMeta *const *fields;
};

typedef struct structMeta structMeta;
struct structMeta {
    typeMetaBase base;
    size_t cnt;
    const fieldMeta *const *fields;
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
    };
};

extern const intMeta uint8_t_meta;

#endif //TYPE_META_H
