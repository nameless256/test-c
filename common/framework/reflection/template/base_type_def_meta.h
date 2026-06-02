#include "mcr_util.h"
#include "type_meta.h"

#ifndef baseTypeName
#error "baseTypeName is not defined"
#endif

#ifndef baseTypeId
#error "baseTypeId is not defined"
#endif

#define baseTypeMetaName cat_2(baseTypeName, meta)

const typeMetaBase baseTypeMetaName = {
    .name = name2Str(baseTypeName),
    .size = sizeof(baseTypeName),
    .quals = qual_Null,
    .id = baseTypeId,
};

#undef baseTypeMetaName
#undef baseTypeName
#undef baseTypeId
