#include "mcr_util.h"
#include "type_meta.h"

#ifndef intName
#error "intName is not defined"
#endif

#define intMetaName cat_2(intName, meta)
#define intMetaFunc(name) cat_2(intMetaName, name)

static const char *intMetaFunc(name)(void) {
    return name2Str(intName);
}

static size_t intMetaFunc(size)(void) {
    return sizeof(intName);
}

static qual intMetaFunc(quals)(void) {
    return qual_Null;
}

static typeId intMetaFunc(id)(void) {
    return typeId_Int;
}

static bool intMetaFunc(isSigned)(void) {
    return (((intName)-1) < 0);
}

const intMeta intMetaName = {
    .base = {
        .name = intMetaFunc(name),
        .size = intMetaFunc(size),
        .quals = intMetaFunc(quals),
        .id = intMetaFunc(id),
    },
    .isSigned = intMetaFunc(isSigned),
};

#undef intMetaName
#undef intMetaFunc
#undef intName
