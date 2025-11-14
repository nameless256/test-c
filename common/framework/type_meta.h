//
// Created by Admin on 25-10-19.
//

#ifndef TYPE_META_H
#define TYPE_META_H

#include <stdbool.h>
#include <stdint.h>

#include "type_def.h"

typedef uint8_t typeId;
enum _typeId {
    typeId_Int,
    typeId_Ptr,
    typeId_Enum,
    typeId_Float,
    typeId_Array,
    typeId_Union,
    typeId_Struct,
};

typedef uint8_t qual;
enum _qual {
    qual_Null = 0b000,
    qual_Const = 0b001,
    qual_Volatile = 0b010,
    qual_Restrict = 0b100,
};

typedef struct _typeMetaBase typeMetaBase;
struct _typeMetaBase {
    const char *name;
    size_t size;
    qual quals;
    typeId id;
};

typedef struct _intMeta intMeta;
struct _intMeta {
    typeMetaBase base;
    bool isSigned;
};

typedef uint8_t ptrTypeId;
enum _ptrTypeId {
    ptrTypeId_Type,
    ptrTypeId_Func,
    ptrTypeId_Array,
};

typedef struct _ptrMetaBase ptrMetaBase;
struct _ptrMetaBase {
    typeMetaBase base;
    ptrTypeId id;
};

typedef struct _typePtrMeta typePtrMeta;
struct _typePtrMeta {
    ptrMetaBase base;
    typeMetaBase *type;
};

typedef struct _paramMeta paramMeta;
struct _paramMeta {
    const typeMetaBase *type;
    const char *name;
};

typedef struct _funcMeta funcMeta;
struct _funcMeta {
    const typeMetaBase *type;
    bool isVarArgs;
    uint8_t cnt;
    const paramMeta *const *params;
};

typedef struct _funcPtrMeta funcPtrMeta;
struct _funcPtrMeta {
    ptrMetaBase base;
    funcMeta *func;
};

typedef struct _arrayMeta arrayMeta;
struct _arrayMeta {
    typeMetaBase base;
    typeMetaBase *type;
    size_t length;
};

typedef struct _arrayPtrMeta arrayPtrMeta;
struct _arrayPtrMeta {
    ptrMetaBase base;
    arrayMeta *array;
};

/**
 * @attention 定义枚举(e.g. enum temp:uint8_t)，需定义枚举值元数据结构
 * @code{.c}
typedef struct _enumValMeta_temp enumValMeta_temp;
struct _enumValMeta_temp {
    enumValMetaBase base;
    uint8_t value;
};
 * @endcode
 */
typedef struct _enumValMetaBase enumValMetaBase;
struct _enumValMetaBase {
    const char *name;
    size_t idx;
};

typedef struct _enumMeta enumMeta;
struct _enumMeta {
    typeMetaBase base;
    typeMetaBase *type;
    size_t cnt;
    const enumValMetaBase *const *tab;
};

typedef struct _fieldMetaBase fieldMetaBase;
struct _fieldMetaBase {
    paramMeta base;
    size_t ofs;
    bool isBitField;
};

typedef struct _bitFieldMeta bitFieldMeta;
struct _bitFieldMeta {
    fieldMetaBase base;
    uint8_t cnt;
    uint8_t ofs;
};

typedef struct _unionMeta unionMeta;
struct _unionMeta {
    typeMetaBase base;
    size_t cnt;
    const fieldMetaBase *const *fields;
};

typedef struct _structMeta structMeta;
struct _structMeta {
    typeMetaBase base;
    size_t cnt;
    const fieldMetaBase *const *fields;
};

#endif //TYPE_META_H
