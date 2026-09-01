#include "meta.h"

#ifdef $access
#undef $access
#endif

#define classStart \
typedef struct className className; \
struct className { \
    classBase base;

#define classEntry(...) classFieldDef(__VA_ARGS__)

#define classEnd }; \
extern const meta_type cat_2(className, meta);
