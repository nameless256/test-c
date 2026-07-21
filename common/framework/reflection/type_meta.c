//
// Created by CodingDev on 2025/12/16.
//
#define TYPE_META_H_IMPL
#include "type_meta.h"

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

bool param_type_meta_parsing(paramMeta *meta) {
    if (meta == NULL) return true;
    if (meta->dsc == NULL) return true;
    if (meta->name == NULL) return true;
    const char *dsc = meta->dsc;
    const char *name = strstr(dsc, meta->name);
    if (name == NULL) return true;
    return false;
}
