//
// Created by CodingDev on 2026/9/2.
//
#include "unicode.h"

#define moduleName unicode

#include "reg_meta_enum.h"
#include "enum_unicode.h"

#include "def_enum_to_string.h"
#include "enum_unicode.h"

#include "reg_meta_enum.h"
#include "enum_unicode_plane.h"

#include "def_enum_to_string.h"
#include "enum_unicode_plane.h"

#include "reg_meta_enum.h"
#include "enum_unicode_size.h"

#include "def_enum_to_string.h"
#include "enum_unicode_size.h"

define(bool, isNochar, unicode cp) {
    if (cp > unicode_Max) return true;
    if ((cp & (unicode_size_Plane - 1)) > unicode_Nonchar) return true;
    if (cp < unicode_BmpNonchar) return false;
    if (cp - unicode_BmpNonchar < unicode_size_BmpNonchar) return true;
    return false;
}

define(bool, isSurrogate, unicode cp) {
    if (cp < unicode_Surrogate) ;
    else if (cp - unicode_Surrogate < unicode_size_Surrogate) return true;
    return false;
}

define(bool, isSurrogateHigh, unicode cp) {
    if (cp < unicode_SurrogateHigh) ;
    else if (cp - unicode_SurrogateHigh < unicode_size_Surrogate / 2) return true;
    return false;
}

define(bool, isSurrogateLow, unicode cp) {
    if (cp < unicode_SurrogateLow) ;
    else if (cp - unicode_SurrogateLow < unicode_size_Surrogate / 2) return true;
    return false;
}

#undef moduleName
