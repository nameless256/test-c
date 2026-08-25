//
// Created by Admin on 26-8-22.
//
#include "meta.h"

#define enumStart \
typedef enumBase enumName; \
enum enumName {

#define enumEntry(...) enumValDef(__VA_ARGS__)

#define enumEnd \
}; \
 \
extern const meta_type cat_2(enumName, meta);