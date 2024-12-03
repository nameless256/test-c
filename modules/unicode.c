//
// Created by xiaoxianghui on 2024/11/15.
//

#include <string.h>
#include "unicode.h"

enum utf8ByteFormat {
    utf8ByteFormat_Illegal = 0,
    utf8ByteFormat_continue = 0,
    utf8ByteFormat_1,
    utf8ByteFormat_2,
    utf8ByteFormat_3,
    utf8ByteFormat_4,
    utf8ByteFormat_Max = 5,
};

static const uint8_t sgUtf8ByteValidBits[utf8ByteFormat_Max] = {6, 7, 5, 4, 3};

static inline bool utf8CheckByte(uint8_t byte, enum utf8ByteFormat format) {
    uint8_t checkBit = 1 << sgUtf8ByteValidBits[format];
    return (uint8_t) (~(byte | (checkBit - 1))) == checkBit;
}

static inline uint32_t uft8GetValByByte(uint8_t byte, enum utf8ByteFormat format) {
    return byte & ((1 << sgUtf8ByteValidBits[format]) - 1);
}

uint32_t unicodeGetCodePointByUtf8(const uint8_t **const utf8) {
    if (utf8 == NULL || *utf8 == NULL) return 0;
    uint8_t bytes = 0;
    for (enum utf8ByteFormat i = utf8ByteFormat_Illegal; i < utf8ByteFormat_Max; ++i) {
        if (!utf8CheckByte((*utf8)[0], i)) continue;
        bytes = i;
        break;
    }
    if (bytes == utf8ByteFormat_Illegal) goto error;
    for (uint8_t i = 1; i < bytes; ++i) {
        if (!utf8CheckByte((*utf8)[i], utf8ByteFormat_continue)) goto error;
    }
    uint32_t codePoint = 0;
    codePoint |= uft8GetValByByte((*utf8)[0], bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        codePoint <<= sgUtf8ByteValidBits[utf8ByteFormat_continue];
        codePoint |= uft8GetValByByte((*utf8)[i], utf8ByteFormat_continue);
    }
    *utf8 += bytes;
    if (codePoint > UNICODE_MAX) codePoint = UNICODE_ERROR;
    return codePoint;
    error:
    *utf8 += 1;
    return UNICODE_ERROR;
}

static inline uint8_t utf8GetCharBitsByFormat(enum utf8ByteFormat format) {
    if (!(utf8ByteFormat_Illegal < format && format < utf8ByteFormat_Max)) return 0;
    uint8_t bits = sgUtf8ByteValidBits[format];
    for (enum utf8ByteFormat i = utf8ByteFormat_1; i < format; ++i) {
        bits += sgUtf8ByteValidBits[utf8ByteFormat_continue];
    }
    return bits;
}

static inline uint8_t utf8GetBytesByCodePoint(uint32_t codePoint) {
    if (codePoint > UNICODE_MAX) return 0;
    for (enum utf8ByteFormat i = utf8ByteFormat_1; i < utf8ByteFormat_Max; ++i) {
        if (codePoint <= (1 << utf8GetCharBitsByFormat(i)) - 1) return i;
    }
    return 0;
}

static inline void utf8SetBytePrefix(uint8_t *const byte, enum utf8ByteFormat format) {
    *byte |= ~((1 << sgUtf8ByteValidBits[format]) - 1);
    *byte &= ~(1 << sgUtf8ByteValidBits[format]);
}

bool unicodeSetUtf8ByCodePoint(uint32_t codePoint, uint8_t **const utf8, size_t utf8Length) {
    if (utf8 == NULL || *utf8 == NULL || codePoint > UNICODE_MAX) return true;
    uint8_t bytes = utf8GetBytesByCodePoint(codePoint);
    if (bytes == 0) return true;
    if (bytes > utf8Length) return true;
    (*utf8)[0] = codePoint >> (sgUtf8ByteValidBits[utf8ByteFormat_continue] * (bytes - 0 - 1));
    utf8SetBytePrefix(&(*utf8)[0], bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        (*utf8)[i] = codePoint >> (sgUtf8ByteValidBits[utf8ByteFormat_continue] * (bytes - i - 1));
        utf8SetBytePrefix(&(*utf8)[i], utf8ByteFormat_continue);
    }
    *utf8 += bytes;
    return false;
}

static inline bool utf16CheckHighSurrogate(uint16_t codeElement) {
    return 0xD800 <= codeElement && codeElement - 0xD800 < 0x400;
}

static inline bool utf16CheckLowSurrogate(uint16_t codeElement) {
    return 0xDC00 <= codeElement && codeElement - 0xDC00 < 0x400;
}

uint32_t unicodeGetCodePointByUtf16(const uint16_t **const utf16) {
    if (utf16 == NULL || *utf16 == NULL) return 0;
    uint32_t codePoint = (*utf16)[0];
    if (utf16CheckHighSurrogate((*utf16)[0])) {
        if (utf16CheckLowSurrogate((*utf16)[1])) {
            codePoint = 0x10000 + (((*utf16)[0] - 0xD800) * 0x400) + ((*utf16)[1] - 0xDC00);
            *utf16 += 1;
        } else {
            // 无效的代理对，处理错误
            codePoint = UNICODE_ERROR;
        }
    } else if (utf16CheckLowSurrogate((*utf16)[0])) {
        codePoint = UNICODE_ERROR;
    }
    *utf16 += 1;
    return codePoint;
}

bool unicodeSetUtf16ByCodePoint(uint32_t codePoint, uint16_t **const utf16, size_t utf16Length) {
    if (utf16 == NULL || *utf16 == NULL || codePoint > UNICODE_MAX) return true;
    if (codePoint >= 0x10000) {
        if (utf16Length < 2) return true;
        (*utf16)[0] = 0xD800 + (codePoint - 0x10000) / 0x400;
        (*utf16)[1] = 0xDC00 + (codePoint - 0x10000) % 0x400;
        *utf16 += 2;
    } else {
        if (utf16Length < 1) return true;
        (*utf16)[0] = codePoint;
        *utf16 += 1;
    }
    return false;
}

size_t unicodeUtf8ToUtf16(const uint8_t *utf8, size_t utf8Length, uint16_t *utf16, size_t utf16Length) {
    const uint8_t *const utf8End = utf8 + utf8Length;
    const uint16_t *const utf16End = utf16 + utf16Length;
    memset(utf16, 0, utf16Length * sizeof(uint16_t));
    while (utf8 < utf8End && utf16 < utf16End && *utf8) {
        uint32_t codePoint = unicodeGetCodePointByUtf8(&utf8);
        if (unicodeSetUtf16ByCodePoint(codePoint, &utf16, utf16End - utf16)) break;
    }
    return utf16Length - (utf16End - utf16);
}

size_t unicodeUtf16ToUtf8(const uint16_t *utf16, size_t utf16Length, uint8_t *utf8, size_t utf8Length) {
    const uint16_t *const utf16End = utf16 + utf16Length;
    const uint8_t *const utf8End = utf8 + utf8Length;
    memset(utf8, 0, utf8Length * sizeof(uint8_t));
    while (utf16 < utf16End && utf8 < utf8End && *utf16) {
        uint32_t codePoint = unicodeGetCodePointByUtf16(&utf16);
        if (unicodeSetUtf8ByCodePoint(codePoint, &utf8, utf8End - utf8)) break;
    }
    return utf8Length - (utf8End - utf8);
}

/// \todo 待验证
bool unicodeGetUtf16LengthByUtf8(const uint8_t *utf8, size_t *const length) {
    if (utf8 == NULL) return 0;
    *length = 0;
    bool characterIllegal = false;
    while (*utf8) {
        uint8_t bytes = 0;
        for (enum utf8ByteFormat i = utf8ByteFormat_Illegal; i < utf8ByteFormat_Max; ++i) {
            if (!utf8CheckByte(utf8[0], i)) continue;
            bytes = i;
            break;
        }
        characterIllegal = bytes == utf8ByteFormat_Illegal;
        if (characterIllegal) break;
        for (uint8_t i = 1; i < bytes; ++i) {
            characterIllegal = !utf8CheckByte(utf8[i], utf8ByteFormat_continue);
            if (characterIllegal) break;
        }
        if (characterIllegal) break;
        if (bytes > 3) *length += 2;
        else *length += 1;
        utf8 += bytes;
    }
    return characterIllegal;
}

/// \todo 待验证
bool unicodeGetUtf8LengthByUtf16(const uint16_t *utf16, size_t *const length) {
    if (utf16 == NULL) return 0;
    *length = 0;
    bool characterIllegal = false;
    while (*utf16) {
        uint8_t bytes = 0;
        if (utf16CheckHighSurrogate(utf16[0])) {
            if (utf16CheckLowSurrogate(utf16[1])) {
                bytes = 4;
            } else {
                characterIllegal = true;
            }
        } else if (utf16CheckLowSurrogate(utf16[0])) {
            characterIllegal = true;
        } else {
            bytes = utf8GetBytesByCodePoint(utf16[0]);
        }
        if (bytes == 0) characterIllegal = true;
        if (characterIllegal) break;
        if (bytes > 3) utf16 += 2;
        else utf16 += 1;
        *length += bytes;
    }
    return characterIllegal;
}

#include "tool.h"
#include <stdio.h>

void unicodeUsage(void) {
    char *demoTexts[] = {
        "Hello, World! 🌍",  // 包含 ASCII 和 BMP 字符
        "👩‍💻👨‍👩‍👧‍👦",  // 包含补充平面中的表情符号
        "你好，世界！",  // 包含中文字符
        "😀😂😍",  // 更多表情符号
    };
    uint16_t utf16[256];
    uint8_t utf8[256];
    for (size_t i = 0; i < ARRAY_SIZE(demoTexts); ++i) {
        printf("Demo %zu: \n", i + 1);
        printBuffer((uint8_t *) demoTexts[i], strlen(demoTexts[i]));
        size_t utf16Size = unicodeUtf8ToUtf16((uint8_t *) demoTexts[i], strlen(demoTexts[i]), utf16, ARRAY_SIZE(utf16));
        size_t utf8Size = unicodeUtf16ToUtf8(utf16, utf16Size, utf8, ARRAY_SIZE(utf8));
        printf("UTF-16: \n");
        printBuffer((uint8_t *) utf16, utf16Size * 2);
        printf("UTF-8: \n");
        printBuffer(utf8, utf8Size);
    }
}

