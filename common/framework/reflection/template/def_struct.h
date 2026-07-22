#include "mcr_util.h"
#include "meta.h"

#ifndef structName
#error "structName is not defined"
#endif

#ifndef structMember
#error "structMember is not defined"
#endif

#ifndef _structMemberDef
#define __structMemberDef2(name, dsc) dsc;
#define _structMemberDef(...) cat2(__structMemberDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#endif

typedef struct structName structName;
struct structName {
    structMember(_structMemberDef)
};

extern const meta_type cat_2(structName, meta);

#ifdef structMataRemain
#undef structMataRemain
#else
#undef structName
#undef structMember
#endif
