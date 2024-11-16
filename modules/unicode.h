//
// Created by xiaoxianghui on 2024/11/15.
//

#ifndef TEST_C_UNICODE_H
#define TEST_C_UNICODE_H

#include <stdint.h>
#include <stdbool.h>

#define UNICODE_ERROR 0xFFFFFFFF
#define UNICODE_MAX 0x0010FFFF

uint32_t unicodeGetCodePointByUtf8(const uint8_t **utf8);

bool unicodeSetUtf8ByCodePoint(uint32_t codePoint, uint8_t **utf8, size_t utf8Size);

uint32_t unicodeGetCodePointByUtf16(const uint16_t **utf16);

bool unicodeSetUtf16ByCodePoint(uint32_t codePoint, uint16_t **utf16, size_t utf16Size);

#endif //TEST_C_UNICODE_H
