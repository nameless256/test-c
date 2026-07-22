#include "mcr_util.h"

#ifndef enumName
#error "enumName is not defined"
#endif

#ifndef enumBase
#define enumBase int
#endif

#ifndef enumMember
#error "enumMember is not defined"
#endif

#ifndef _enumMemberDef
#define __enumMemberDef1(name) cat_2(enumName, name),
#define __enumMemberDef2(name, value) cat_2(enumName, name) = value,
#define _enumMemberDef(...) cat2(__enumMemberDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#endif

typedef enumBase enumName;
enum enumName {
    enumMember(_enumMemberDef)
};

extern const meta_type cat_2(enumName, meta);

#ifdef enumMataRemain
#undef enumMataRemain
#else
#undef enumName
#undef enumBase
#undef enumMember
#endif
