//
// Created by xiaoxianghui on 2024/11/15.
//

#include <assert.h>
#include "unicode.h"
#include "tool.h"

enum utf8ByteFormat {
    utf8ByteFormat_Illegal = 0,
    utf8ByteFormat_continue = 0,
    utf8ByteFormat_0 UNUSED = 0,
    utf8ByteFormat_1 UNUSED,
    utf8ByteFormat_2 UNUSED,
    utf8ByteFormat_3 UNUSED,
    utf8ByteFormat_4 UNUSED,
    utf8ByteFormat_Max = 5,
};

static const uint8_t sgUtf8ByteValidBits[utf8ByteFormat_Max] = {6, 7, 5, 4, 3};

#define utf8CheckByte(byte, format) (((~(byte) >> sgUtf8ByteValidBits[format]) & 1) == 1)
#define uft8GetValByByte(byte, format) ((byte) & ((1 << sgUtf8ByteValidBits[format]) - 1))

uint32_t unicodeGetUtf32CharByUtf8(const uint8_t **const utf8) {
    if (utf8 == NULL || *utf8 == NULL) return 0;
    uint8_t bytes = 0;
    for (enum utf8ByteFormat i = utf8ByteFormat_Illegal; i < utf8ByteFormat_Max; ++i) {
        if (!utf8CheckByte(**utf8, i)) continue;
        bytes = i;
        break;
    }
    if (bytes == utf8ByteFormat_Illegal) goto error;
    for (uint8_t i = 1; i < bytes; ++i) {
        if (!utf8CheckByte(*(*utf8 + i), utf8ByteFormat_continue)) goto error;
    }
    uint32_t codePoint = 0;
    codePoint |= uft8GetValByByte(*(*utf8 + 0), bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        codePoint <<= sgUtf8ByteValidBits[utf8ByteFormat_continue];
        codePoint |= uft8GetValByByte(*(*utf8 + i), utf8ByteFormat_continue);
    }
    *utf8 += bytes;
    if (codePoint > UTF32_MAX) codePoint = UTF32_ERROR;
    return codePoint;
    error:
    *utf8 += 1;
    return UTF32_ERROR;
}

uint32_t unicodeGetUtf32CharByUtf16(const uint16_t **const utf16) {
    if (utf16 == NULL || *utf16 == NULL) return 0;
    uint32_t codePoint = **utf16;
    if (codePoint >= 0xD800 && codePoint <= 0xDBFF) { // 高代理对
        uint16_t lowSurrogate = *(*utf16 + 1);
        if (lowSurrogate >= 0xDC00 && lowSurrogate <= 0xDFFF) { // 低代理对
            codePoint = 0x10000 + ((codePoint - 0xD800) << 10) + (lowSurrogate - 0xDC00);
            *utf16 += 1;
        } else {
            // 无效的代理对，处理错误
            codePoint = UTF32_ERROR;
        }
    } else if (codePoint >= 0xDC00 && codePoint <= 0xDFFF) {
        codePoint = UTF32_ERROR;
    }
    *utf16 += 1;
    return codePoint;
}

static inline uint8_t getUtf8CharBitsByFormat(enum utf8ByteFormat format) {
    if (!(utf8ByteFormat_0 < format && format < utf8ByteFormat_Max)) return 0;
    uint8_t bits = sgUtf8ByteValidBits[format];
    for (enum utf8ByteFormat i = utf8ByteFormat_1; i < format; ++i) {
        bits += sgUtf8ByteValidBits[utf8ByteFormat_continue];
    }
    return bits;
}

static inline uint8_t getUtf8BytesByCodePoint(uint32_t codePoint) {
    for (enum utf8ByteFormat i = utf8ByteFormat_1; i < utf8ByteFormat_Max; ++i) {
        if (codePoint <= (1 << getUtf8CharBitsByFormat(i)) - 1) return i;
    }
    return 0;
}

bool unicodeSetUtf8ByUtf32Char(uint32_t codePoint, uint8_t **const utf8, size_t utf8Size) {
    if (utf8 == NULL || *utf8 == NULL || codePoint > UTF32_MAX) return true;
    uint8_t bytes = getUtf8BytesByCodePoint(codePoint);
    if (bytes == 0) return true;
    return false;
}

