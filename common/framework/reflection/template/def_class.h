#include "meta.h"

#ifdef accessCtrl
#undef accessCtrl
#endif

#define classStart \
typedef struct className className; \
struct className { \
    union { \
        struct { \
            const meta_type *meta; \
            cat_2(className, vtab) *vtab; \
        }; \
        classBase base; \
    };

#define classEntry(...) classFieldDef(__VA_ARGS__)

#define classEnd }; \
extern const meta_type cat_2(className, meta);
