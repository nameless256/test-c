//
// Created by CodingDev on 2026/9/3.
//

#ifndef TEST_C_UTF8_H
#define TEST_C_UTF8_H

#include "unicode.h"

#define moduleName utf8

declare(unicode, decode, const uint8_t *utf8, uint8_t *ofs);

declare(uint8_t, encode, unicode cp, uint8_t *const utf8, size_t utf8Length);

#undef moduleName

#endif //TEST_C_UTF8_H
