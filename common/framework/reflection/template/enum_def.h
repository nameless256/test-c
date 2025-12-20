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
#define __enumMemberDef1(tuple) cat_2(enumName, mcrVaTuple(tuple, 0)),
#define __enumMemberDef2(tuple) cat_2(enumName, mcrVaTuple(tuple, 0)) = mcrVaTuple(tuple, 1),
#define _enumMemberDef(tuple) cat2(__enumMemberDef, mcrVaTupleArgCount(tuple)) (tuple)
#endif

typedef enumBase enumName;
enum enumName {
    mcrIter(_enumMemberDef, enumMember)
};

#ifdef enumMataRemain
#undef enumMataRemain
#else
#undef enumName
#undef enumBase
#undef enumMember
#endif
