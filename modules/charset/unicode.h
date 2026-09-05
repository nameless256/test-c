//
// Created by CodingDev on 2025/12/17.
//

#ifndef TEST_C_UNICODE_H
#define TEST_C_UNICODE_H

#define moduleName unicode

#include "def_enum.h"
#include "enum_unicode.h"

#include "def_enum.h"
#include "enum_unicode_plane.h"

#include "def_enum.h"
#include "enum_unicode_size.h"

declare(bool, isNochar, unicode cp);

declare(bool, isSurrogate, unicode cp);

declare(bool, isSurrogateHigh, unicode cp);

declare(bool, isSurrogateLow, unicode cp);

#undef moduleName

#endif //TEST_C_UNICODE_H