#include "mcr_util.h"
#include "meta.h"

#ifndef className
#error "className is not defined"
#endif

#ifndef classBaseName
#define classBaseName objBase
#endif

#ifndef _classMemberDef
#define __classMemberDef3(name, dsc, bits) dsc: bits;
#define __classMemberDef2(name, dsc) dsc;
#define _classMemberDef(...) cat2(__classMemberDef, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)
#endif

typedef struct className className;
struct className {
    classBaseName base;
#ifdef classMember
    classMember(_classMemberDef)
#endif
};

extern const meta_type cat_2(className, meta);
extern bool cat_2(className, ctor)(objBase *);
extern void cat_2(className, dtor)(objBase *);
extern bool cat_2(className, copy)(objBase *, objBase *);

#ifdef classMataRemain
#undef classMataRemain
#else
#undef className
#ifdef classMember
#undef classMember
#endif
#undef classBaseName
#endif
