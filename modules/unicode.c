//
// Created by xiaoxianghui on 2024/11/15.
//

#include <string.h>
#include <malloc.h>

#include "unicode.h"

enum utf8ByteFormat {
    utf8ByteFormat_Illegal = 0,
    utf8ByteFormat_Continue = 0,
    utf8ByteFormat_1,
    utf8ByteFormat_2,
    utf8ByteFormat_3,
    utf8ByteFormat_4,
    utf8ByteFormat_Max = 5,
};

static const uint8_t sUtf8ByteValidBits[utf8ByteFormat_Max] = {6, 7, 5, 4, 3};

static inline bool utf8CheckByte(uint8_t byte, enum utf8ByteFormat format) {
    uint8_t checkBit = 1 << sUtf8ByteValidBits[format];
    return (uint8_t) (~(byte | (checkBit - 1))) == checkBit;
}

static inline uint32_t uft8GetValByByte(uint8_t byte, enum utf8ByteFormat format) {
    return byte & ((1 << sUtf8ByteValidBits[format]) - 1);
}

static uint8_t utf8GetCharCodingUnit(const uint8_t *utf8) {
    uint8_t bytes = 0;
    for (enum utf8ByteFormat i = utf8ByteFormat_Illegal; i < utf8ByteFormat_Max; ++i) {
        if (!utf8CheckByte(utf8[0], i)) continue;
        bytes = i;
        break;
    }
    for (uint8_t i = 1; i < bytes; ++i) {
        if (utf8CheckByte(utf8[i], utf8ByteFormat_Continue)) continue;
        bytes = 0;
        break;
    }
    return bytes;
}

uint32_t unicodeGetCodePointByUtf8(const uint8_t **const utf8) {
    if (utf8 == NULL || *utf8 == NULL) return UNICODE_ERROR;
    uint8_t bytes = utf8GetCharCodingUnit(*utf8);
    if (bytes == 0) goto error;
    uint32_t codePoint = 0;
    codePoint |= uft8GetValByByte((*utf8)[0], bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        codePoint <<= sUtf8ByteValidBits[utf8ByteFormat_Continue];
        codePoint |= uft8GetValByByte((*utf8)[i], utf8ByteFormat_Continue);
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
    uint8_t bits = sUtf8ByteValidBits[format];
    for (enum utf8ByteFormat i = utf8ByteFormat_1; i < format; ++i) {
        bits += sUtf8ByteValidBits[utf8ByteFormat_Continue];
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
    *byte |= ~((1 << sUtf8ByteValidBits[format]) - 1);
    *byte &= ~(1 << sUtf8ByteValidBits[format]);
}

bool unicodeSetUtf8ByCodePoint(uint32_t codePoint, uint8_t **const utf8, size_t utf8Length) {
    if (utf8 == NULL || *utf8 == NULL || codePoint > UNICODE_MAX) return true;
    uint8_t bytes = utf8GetBytesByCodePoint(codePoint);
    if (bytes == 0) return true;
    if (bytes > utf8Length) return true;
    (*utf8)[0] = codePoint >> (sUtf8ByteValidBits[utf8ByteFormat_Continue] * (bytes - 0 - 1));
    utf8SetBytePrefix(&(*utf8)[0], bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        (*utf8)[i] = codePoint >> (sUtf8ByteValidBits[utf8ByteFormat_Continue] * (bytes - i - 1));
        utf8SetBytePrefix(&(*utf8)[i], utf8ByteFormat_Continue);
    }
    *utf8 += bytes;
    return false;
}

#define SUR_START_HIGH  0xD800
#define SUR_START_LOW   0xDC00
#define SUR_SIZE    0x400
#define SP_START    0x10000

static inline bool utf16CheckHighSurrogate(uint16_t codeElement) {
    return SUR_START_HIGH <= codeElement && codeElement - SUR_START_HIGH < SUR_SIZE;
}

static inline bool utf16CheckLowSurrogate(uint16_t codeElement) {
    return SUR_START_LOW <= codeElement && codeElement - SUR_START_LOW < SUR_SIZE;
}

static inline uint8_t utf16GetCharCodingUnit(const uint16_t *utf16) {
    uint8_t codingUnit = 0;
    if (utf16CheckHighSurrogate(utf16[0])) {
        if (utf16CheckLowSurrogate(utf16[1])) {
            codingUnit = 2;
        }
    } else if (!utf16CheckLowSurrogate(utf16[0])) {
        codingUnit = 1;
    }
    return codingUnit;
}

uint32_t unicodeGetCodePointByUtf16(const uint16_t **const utf16) {
    if (utf16 == NULL || *utf16 == NULL) return UNICODE_ERROR;
    uint32_t codePoint = (*utf16)[0];
    uint8_t codingUnit = utf16GetCharCodingUnit(*utf16);
    if (codingUnit == 2) {
        codePoint = SP_START + (((*utf16)[0] - SUR_START_HIGH) * SUR_SIZE) + ((*utf16)[1] - SUR_START_LOW);
    } else if (codingUnit == 0) {
        codePoint = UNICODE_ERROR;
    }
    *utf16 += codingUnit == 2 ? 2 : 1;
    return codePoint;
}

bool unicodeSetUtf16ByCodePoint(uint32_t codePoint, uint16_t **const utf16, size_t utf16Length) {
    if (utf16 == NULL || *utf16 == NULL || codePoint > UNICODE_MAX) return true;
    if (codePoint >= SP_START) {
        if (utf16Length < 2) return true;
        (*utf16)[0] = SUR_START_HIGH + (codePoint - SP_START) / SUR_SIZE;
        (*utf16)[1] = SUR_START_LOW + (codePoint - SP_START) % SUR_SIZE;
        *utf16 += 2;
    } else {
        if (utf16Length < 1) return true;
        (*utf16)[0] = codePoint;
        *utf16 += 1;
    }
    return false;
}

size_t unicodeUtf8ToUtf16(const uint8_t *utf8, size_t utf8Length, uint16_t *utf16, size_t utf16Length) {
    if (utf8 == NULL || utf16 == NULL) return 0;
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
    if (utf16 == NULL || utf8 == NULL) return 0;
    const uint16_t *const utf16End = utf16 + utf16Length;
    const uint8_t *const utf8End = utf8 + utf8Length;
    memset(utf8, 0, utf8Length * sizeof(uint8_t));
    while (utf16 < utf16End && utf8 < utf8End && *utf16) {
        uint32_t codePoint = unicodeGetCodePointByUtf16(&utf16);
        if (unicodeSetUtf8ByCodePoint(codePoint, &utf8, utf8End - utf8)) break;
    }
    return utf8Length - (utf8End - utf8);
}

size_t unicodeGetUtf8Length(const uint8_t *utf8) {
    if (utf8 == NULL) return 0;
    size_t length = 0;
    while (*utf8) {
        uint8_t bytes = utf8GetCharCodingUnit(utf8);
        if (bytes == 0) {
            length = 0;
            break;
        }
        length += bytes;
        utf8 += bytes;
    }
    return length;
}

size_t unicodeGetUtf16Length(const uint16_t *utf16) {
    if (utf16 == NULL) return 0;
    size_t length = 0;
    while (*utf16) {
        uint8_t codingUnit = utf16GetCharCodingUnit(utf16);
        if (codingUnit == 0) {
            length = 0;
            break;
        }
        length += codingUnit;
        utf16 += codingUnit;
    }
    return length;
}

size_t unicodeGetUtf8LengthByUtf16(const uint16_t *utf16) {
    if (utf16 == NULL) return 0;
    size_t length = 0;
    while (*utf16) {
        uint8_t codingUnit = utf16GetCharCodingUnit(utf16);
        if (codingUnit == 0) {
            length = 0;
            break;
        }
        length += codingUnit == 2 ? 4 : utf8GetBytesByCodePoint(utf16[0]);
        utf16 += codingUnit;
    }
    return length;
}

size_t unicodeGetUtf16LengthByUtf8(const uint8_t *utf8) {
    if (utf8 == NULL) return 0;
    size_t length = 0;
    while (*utf8) {
        uint8_t bytes = utf8GetCharCodingUnit(utf8);
        if (bytes == 0) {
            length = 0;
            break;
        }
        length += bytes > 3 ? 2 : 1;
        utf8 += bytes;
    }
    return length;
}

uint8_t *unicodeGetUtf8ByUtf16(const uint16_t *utf16) {
    if (utf16 == NULL) return NULL;
    size_t length = unicodeGetUtf8LengthByUtf16(utf16);
    if (length == 0) return NULL;
    length++;
    uint8_t *utf8 = calloc(length, sizeof(uint8_t));
    unicodeUtf16ToUtf8(utf16, unicodeGetUtf16Length(utf16), utf8, length);
    return utf8;
}

uint16_t *unicodeGetUtf16ByUtf8(const uint8_t *utf8) {
    if (utf8 == NULL) return NULL;
    size_t length = unicodeGetUtf16LengthByUtf8(utf8);
    if (length == 0) return NULL;
    length++;
    uint16_t *utf16 = calloc(length, sizeof(uint16_t));
    unicodeUtf8ToUtf16(utf8, unicodeGetUtf8Length(utf8), utf16, length);
    return utf16;
}

struct utfBOMInfo {
    uint8_t size;
    uint8_t const *bytes;
} static const sgUtfBOM[utfBom_Max] = {
    {0, (const uint8_t[]) {},},
    {3, (const uint8_t[]) {0xef, 0xbb, 0xbf},},
    {2, (const uint8_t[]) {0xff, 0xfe},},
    {2, (const uint8_t[]) {0xfe, 0xff},},
    {4, (const uint8_t[]) {0xff, 0xfe, 0x00, 0x00},},
    {4, (const uint8_t[]) {0x00, 0x00, 0xfe, 0xff},},
};

static inline bool utfCheckBom(const uint8_t *stream, enum utfBom checkBOM) {
    if (checkBOM == utfBom_Utf16_LE && (stream[2] == 0x00 && stream[3] == 0x00)) return false;
    for (uint8_t i = 0; i < sgUtfBOM[checkBOM].size; ++i) {
        if (stream[i] != sgUtfBOM[checkBOM].bytes[i]) return false;
    }
    return true;
}

enum utfBom unicodeUtfCheckBom(const uint8_t *stream, size_t streamLength) {
    if (stream == NULL) return utfBom_None;
    for (enum utfBom checkBOM = utfBom_Utf8; checkBOM < utfBom_Max; ++checkBOM) {
        if (streamLength < sgUtfBOM[checkBOM].size) continue;
        if (utfCheckBom(stream, checkBOM)) return checkBOM;
    }
    return utfBom_None;
}

uint8_t unicodeUtfGetBomSize(enum utfBom bom) {
    return sgUtfBOM[bom].size;
}

uint8_t const *unicodeUtfGetBomBytes(enum utfBom bom) {
    return sgUtfBOM[bom].bytes;
}

#include <stdio.h>
#include "util.h"

void unicodeUsage(void) {
    char *demoTexts[] = {
        "Hello, World! 🌍",  // 包含 ASCII 和 BMP 字符
        "👩‍💻👨‍👩‍👧‍👦",  // 包含补充平面中的表情符号
        "你好，世界！",  // 包含中文字符
        "😀😂😍",  // 更多表情符号
    };
#if 0
    uint16_t utf16[256];
    uint8_t utf8[256];
    for (size_t i = 0; i < ARRAY_SIZE(demoTexts); ++i) {
        printf("Demo %zu: \n", i + 1);
        printBuffer((uint8_t *) demoTexts[i], strlen(demoTexts[i]));
        size_t utf16Length = unicodeUtf8ToUtf16((uint8_t *) demoTexts[i], strlen(demoTexts[i]), utf16, 256);
        size_t utf8Length = unicodeUtf16ToUtf8(utf16, utf16Length, utf8, 256);
        printf("UTF-16: \n");
        printBuffer((uint8_t *) utf16, utf16Length * sizeof(uint16_t));
        printf("UTF-8: \n");
        printBuffer(utf8, utf8Length);
    }
#elif 0
    for (size_t i = 0; i < ARRAY_SIZE(demoTexts); ++i) {
        printf("Demo %zu: \n", i + 1);
        printBuffer((uint8_t *) demoTexts[i], strlen(demoTexts[i]));
        uint16_t *utf16 = unicodeGetUtf16ByUtf8((uint8_t *) demoTexts[i]);
        if (utf16 == NULL) {
            printf("UTF-16: NULL\n");
            continue;
        }
        uint8_t *utf8 = unicodeGetUtf8ByUtf16(utf16);
        if (utf8 == NULL) {
            printf("UTF-8: NULL\n");
            free(utf16), utf16 = NULL;
            continue;
        }
        printf("UTF-16: \n");
        printBuffer((uint8_t *) utf16, unicodeGetUtf16Length(utf16) * sizeof(uint16_t));
        printf("UTF-8: \n");
        printBuffer(utf8, unicodeGetUtf8Length(utf8));
        free(utf16), utf16 = NULL;
        free(utf8), utf8 = NULL;
    }
#elif 1
    /// \attention 不以二进制文件打开，而是以文本文件打开，会更据不同的平台对换行符进行转换，如'\\n'->'\\r\\n'
    /// \attention 读的时候也会进行逆转换，如'\\r\\n'->'\\n'，从而导致后面读取到错误的数据
    autoReleaseFile(fp, "..\\ignore\\test.txt", "wb+") {
        fwrite(unicodeUtfGetBomBytes(utfBom_Utf8), unicodeUtfGetBomSize(utfBom_Utf8), 1, fp);
        for (int i = 0; i < ARRAY_SIZE(demoTexts); ++i) {
            fprintf(fp, "%s\n", demoTexts[i]);
        }
    }
    autoReleaseFile(fp, "..\\ignore\\test.txt", "rb") {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET); // 重置文件指针到开头
        uint8_t buffer[size + 1];
        fread(buffer, 1, size, fp);
        buffer[size] = '\0';
        enum utfBom bom = unicodeUtfCheckBom(buffer, size);
        printf("[%d] --------- {%s} bom %d \n", __LINE__, __FUNCTION__, bom);
        uint8_t *reader = buffer + unicodeUtfGetBomSize(bom);
        printf("%s", reader);
        printBuffer(buffer, size);
    }
#endif
}

