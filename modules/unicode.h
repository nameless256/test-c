//
// Created by xiaoxianghui on 2024/11/15.
//

#ifndef TEST_C_UNICODE_H
#define TEST_C_UNICODE_H

#include <stdint.h>

#define UTF32_ERROR 0xFFFFFFFF
#define UTF32_MAX 0x0010FFFF

uint32_t unicodeGetUtf32CharByUtf8(const uint8_t **utf8);

uint32_t unicodeGetUtf32CharByUtf16(const uint16_t **utf16);

#endif //TEST_C_UNICODE_H
