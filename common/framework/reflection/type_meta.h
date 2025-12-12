//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>

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
    typeMetaBase *type;
};

typedef struct paramMeta paramMeta;
struct paramMeta {
    const typeMetaBase *type;
    const char *name;
};

typedef struct funcMeta funcMeta;
struct funcMeta {
    const typeMetaBase *type;
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
    typeMetaBase *type;
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

/**
 * @attention 定义枚举(e.g. enum temp:uint8_t)，需定义枚举值元数据结构
 * @code{.c}
typedef struct enumValMeta_temp enumValMeta_temp;
struct enumValMeta_temp {
    enumValMetaBase base;
    uint8_t value;
};
 * @endcode
 */
typedef struct enumValMetaBase enumValMetaBase;
struct enumValMetaBase {
    const char *name;
    size_t idx;
};

typedef struct enumMeta enumMeta;
struct enumMeta {
    typeMetaBase base;
    typeMetaBase *type;
    size_t cnt;
    const enumValMetaBase *const *tab;
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

typedef struct typeMeta typeMeta;
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

#endif //TYPE_META_H
