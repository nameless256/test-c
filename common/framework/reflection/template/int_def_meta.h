#include "mcr_util.h"
#include "meta.h"

#ifndef intName
#error "intName is not defined"
#endif

#define intMetaName cat_2(intName, meta)

const meta_int intMetaName = {
    .base = {
        .name = name2Str(intName),
        .size = sizeof(intName),
        .quals = qual_Null,
        .id = typeId_Int,
    },
    .isSigned = (((intName)-1) < 0),
};

#undef intMetaName
#undef intName
