//
// Created by CodingDev on 2025/12/16.
//
#define TYPE_META_H_IMPL
#include "meta.h"

#define intName int8_t
#include "def_meta_int.h"
#define intName uint8_t
#include "def_meta_int.h"
#define intName int16_t
#include "def_meta_int.h"
#define intName uint16_t
#include "def_meta_int.h"
#define intName int32_t
#include "def_meta_int.h"
#define intName uint32_t
#include "def_meta_int.h"
#define intName int64_t
#include "def_meta_int.h"
#define intName uint64_t
#include "def_meta_int.h"
#define intName size_t
#include "def_meta_int.h"
#define intName char
#include "def_meta_int.h"

#define baseTypeName bool
#define baseTypeId typeId_Bool
#include "def_meta_base_type.h"

#define baseTypeName float
#define baseTypeId typeId_Float
#include "def_meta_base_type.h"

#define baseTypeName double
#define baseTypeId typeId_Float
#include "def_meta_base_type.h"

bool param_type_meta_parsing(meta_param *meta) {
    if (meta == NULL) return true;
    if (meta->dsc == NULL) return true;
    if (meta->name == NULL) return true;
    const char *dsc = meta->dsc;
    const char *name = strstr(dsc, meta->name);
    // int a
    // signed int a
    // unsigned int a
    // const char *name
    // union {
    //     typeMeta *type;
    //     funcMeta *func;
    //     arrayMeta *array;
    // }
    // const enumValMeta *const vals
    // bool (*ctor)(objBase *)
    // ptrTypeId id
    // ptrTypeId id[3]
    // uint8_t t:4
    // void (*t[10]) (int a)
    // int (*t)[10]
    // void *t[10]
    if (name == NULL) return true;
    return false;
}
