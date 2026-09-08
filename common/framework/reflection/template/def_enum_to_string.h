//
// Created by CodingDev on 2026/8/26.
//
#include "meta.h"

#define enumStart \
const char *cat_2(enumName, toString) (enumName value, bool full) { \

#define enumEntry(name, ...) \
    if (value == cat_2(enumName, name)) \
        return nameVal2Str(cat_2(enumName, name)) + (full ? 0 : sizeof(nameVal2Str(enumName)));

#define enumEnd \
    return "NaEN"; \
}
