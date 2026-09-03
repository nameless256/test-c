//
// Created by CodingDev on 2026/9/3.
//

#include "utf8.h"

#define moduleName utf8

#include "def_enum.h"
#define enumName utf8_byteFmt
#define enumBase uint8_t
enumStart
    enumEntry(Continue, 0)
    enumEntry(1)
    enumEntry(2)
    enumEntry(3)
    enumEntry(4)
    enumEntry(Illegal, 5)
    enumEntry(Max, 5)
enumEnd

#include "clean_up_enum.h"

static const uint8_t sCodeUnitValidBits[utf8_byteFmt_Max] = {6, 7, 5, 4, 3};

static inline bool checkFmt(uint8_t codeUnit, utf8_byteFmt fmt) {
    uint8_t checkBit = 1 << sCodeUnitValidBits[fmt];
    return (uint8_t) (~(codeUnit | (checkBit - 1))) == checkBit;
}

static inline uint32_t getVal(uint8_t codeUnit, utf8_byteFmt fmt) {
    return codeUnit & ((1 << sCodeUnitValidBits[fmt]) - 1);
}

static utf8_byteFmt getFmt(uint8_t codeUnit) {
    utf8_byteFmt fmt = utf8_byteFmt_Illegal;
    for (utf8_byteFmt i = utf8_byteFmt_Continue; i < utf8_byteFmt_Max; ++i) {
        if (checkFmt(codeUnit, i)) {
            fmt = i;
            break;
        }
    }
    return fmt;
}

define(unicode, decode, const uint8_t *utf8, uint8_t *ofs) {
    if (utf8 == NULL) return unicode_Nonchar;
    utf8_byteFmt fmt = getFmt(utf8[0]);
    *ofs += 1;
    if (fmt == utf8_byteFmt_Continue || fmt == utf8_byteFmt_Illegal) return unicode_Nonchar;
    unicode cp = getVal(utf8[0], fmt);
    for (uint8_t i = 1; i < fmt; ++i) {
        *ofs += 1;
        if (checkFmt(utf8[i], utf8_byteFmt_Continue)) {
            cp <<= sCodeUnitValidBits[utf8_byteFmt_Continue];
            cp |= getVal(utf8[i], utf8_byteFmt_Continue);
        } else {
            cp = unicode_Nonchar;
            break;
        }
    }
    if (cp > unicode_Max) cp = unicode_Nonchar;
    return cp;
}

static inline uint8_t getCharBitsByFmt(utf8_byteFmt fmt) {
    if (fmt >= utf8_byteFmt_Max) return 0;
    uint8_t bits = sCodeUnitValidBits[fmt];
    for (uint8_t i = 1; i < fmt; ++i) {
        bits += sCodeUnitValidBits[utf8_byteFmt_Continue];
    }
    return bits;
}

static inline uint8_t getBytes(unicode cp) {
    if (cp > unicode_Max) return 0;
    for (utf8_byteFmt i = utf8_byteFmt_1; i < utf8_byteFmt_Max; ++i) {
        if (cp <= (1 << getCharBitsByFmt(i)) - 1) return i;
    }
    return 0;
}

static inline void utf8SetBytePrefix(uint8_t *const byte, utf8_byteFmt fmt) {
    *byte |= ~((1 << sCodeUnitValidBits[fmt]) - 1);
    *byte &= ~(1 << sCodeUnitValidBits[fmt]);
}

define(uint8_t, encode, unicode cp, uint8_t *const utf8, size_t utf8Length) {
    if (utf8 == NULL || cp > unicode_Max) return 0;
    uint8_t bytes = getBytes(cp);
    if (bytes == 0) return 0;
    if (bytes > utf8Length) return 0;
    utf8[0] = cp >> (sCodeUnitValidBits[utf8_byteFmt_Continue] * (bytes - 0 - 1));
    utf8SetBytePrefix(&utf8[0], bytes);
    for (uint8_t i = 1; i < bytes; ++i) {
        utf8[i] = cp >> (sCodeUnitValidBits[utf8_byteFmt_Continue] * (bytes - i - 1));
        utf8SetBytePrefix(&utf8[i], utf8_byteFmt_Continue);
    }
    return bytes;
}

#undef moduleName
