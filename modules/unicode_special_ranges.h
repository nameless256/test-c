/**
 * unicode_special_ranges.h
 *
 * Unicode 特殊码点范围枚举 — 覆盖代理区、私用区、非字符、控制字符、
 * BOM、零宽字符、组合字符、异体字选择符等所有关键特殊区域。
 *
 * C99 纯 C，零依赖，-Wall -Wextra 无警告。
 *
 * 用法示例：
 *   uint32_t cp = 0xD83D;
 *   UnicodeSpecialRange r = UnicodeRangeLookup(cp);
 *   if (r != (UnicodeSpecialRange)(-1))
 *       printf("0x%04X -> %s\n", cp, kUnicodeRanges[r].desc);
 */

#ifndef UNICODE_SPECIAL_RANGES_H
#define UNICODE_SPECIAL_RANGES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ===================================================================
 * 枚举定义 — 每个值对应一个特殊码点范围
 * =================================================================== */
typedef enum {
    /* ---- 控制字符 ---- */
    UnicodeRangeC0Control,          /* U+0000  ~ U+001F  C0 控制字符                   */
    UnicodeRangeC1Control,          /* U+0080  ~ U+009F  C1 控制字符                   */

    /* ---- 代理区 ---- */
    UnicodeRangeSurrogate,          /* U+D800  ~ U+DFFF  代理区（Surrogate Pair）       */

    /* ---- 私用区 ---- */
    UnicodeRangePuaBmp,             /* U+E000  ~ U+F8FF  BMP 私用区（PUA）              */
    UnicodeRangePuaPlane15,         /* U+F0000 ~ U+FFFFF Plane 15 私用区（PUA-A）       */
    UnicodeRangePuaPlane16,         /* U+100000~ U+10FFFF Plane 16 私用区（PUA-B）      */

    /* ---- 非字符（Noncharacters） ---- */
    UnicodeRangeNoncharBmp,         /* U+FDD0  ~ U+FDEF  BMP 非字符范围                */
    UnicodeRangeNoncharBmpEnd,      /* U+FFFE, U+FFFF     BMP 结尾非字符               */
    UnicodeRangeNoncharSmp,         /* U+1FFFE, U+1FFFF   SMP 结尾非字符               */
    UnicodeRangeNoncharSip,         /* U+2FFFE, U+2FFFF   SIP 结尾非字符               */
    UnicodeRangeNoncharTip,         /* U+3FFFE, U+3FFFF   TIP 结尾非字符               */
    UnicodeRangeNoncharHigh,        /* U+4FFFE ~ U+10FFFE 各平面结尾非字符（通用规则）  */

    /* ---- BOM / 零宽 / 特殊空白 ---- */
    UnicodeRangeBom,                /* U+FEFF            BOM / 零宽不换行空格          */
    UnicodeRangeZeroWidth,          /* U+200B ~ U+200D   零宽空格 / 非连接符 / 连接符   */
    UnicodeRangeWordJoiner,         /* U+2060            单词连接符                     */

    /* ---- 组合字符 ---- */
    UnicodeRangeCombiningDiacritical,    /* U+0300 ~ U+036F  组合变音符号              */
    UnicodeRangeCombiningSymbols,        /* U+20D0 ~ U+20FF  组合用符号                */
    UnicodeRangeVariationSelector,       /* U+FE00 ~ U+FE0F  异体字选择符（VS1-VS16）  */
    UnicodeRangeVariationSelectorSupp,   /* U+E0100~ U+E01EF 异体字选择符补充（VS17-VS256） */

    UnicodeRangeCount
} UnicodeSpecialRange;

/* ===================================================================
 * 范围元数据表
 * =================================================================== */
typedef struct {
    UnicodeSpecialRange id;
    uint32_t            start;
    uint32_t            end;
    const char*         category;
    const char*         desc;
} UnicodeRangeEntry;

static const UnicodeRangeEntry kUnicodeRanges[UnicodeRangeCount] = {
    { UnicodeRangeC0Control,          0x0000,   0x001F,   "Cc", "C0 控制字符" },
    { UnicodeRangeC1Control,          0x0080,   0x009F,   "Cc", "C1 控制字符" },
    { UnicodeRangeSurrogate,          0xD800,   0xDFFF,   "Cs", "代理区（Surrogate Pair）" },
    { UnicodeRangePuaBmp,             0xE000,   0xF8FF,   "Co", "BMP 私用区（PUA）" },
    { UnicodeRangePuaPlane15,         0xF0000,  0xFFFFF,  "Co", "Plane 15 私用区（PUA-A）" },
    { UnicodeRangePuaPlane16,         0x100000, 0x10FFFF, "Co", "Plane 16 私用区（PUA-B）" },
    { UnicodeRangeNoncharBmp,         0xFDD0,   0xFDEF,   "Cn", "BMP 非字符范围" },
    { UnicodeRangeNoncharBmpEnd,      0xFFFE,   0xFFFF,   "Cn", "BMP 结尾非字符" },
    { UnicodeRangeNoncharSmp,         0x1FFFE,  0x1FFFF,  "Cn", "SMP 结尾非字符" },
    { UnicodeRangeNoncharSip,         0x2FFFE,  0x2FFFF,  "Cn", "SIP 结尾非字符" },
    { UnicodeRangeNoncharTip,         0x3FFFE,  0x3FFFF,  "Cn", "TIP 结尾非字符" },
    { UnicodeRangeNoncharHigh,        0x4FFFE,  0x10FFFE, "Cn", "各平面结尾非字符（通用规则）" },
    { UnicodeRangeBom,                0xFEFF,   0xFEFF,   "Cf", "BOM / 零宽不换行空格" },
    { UnicodeRangeZeroWidth,          0x200B,   0x200D,   "Cf", "零宽空格 / 非连接符 / 连接符" },
    { UnicodeRangeWordJoiner,         0x2060,   0x2060,   "Cf", "单词连接符" },
    { UnicodeRangeCombiningDiacritical,     0x0300,   0x036F,   "Mn", "组合变音符号" },
    { UnicodeRangeCombiningSymbols,         0x20D0,   0x20FF,   "Mn", "组合用符号" },
    { UnicodeRangeVariationSelector,        0xFE00,   0xFE0F,   "Mn", "异体字选择符（VS1-VS16）" },
    { UnicodeRangeVariationSelectorSupp,    0xE0100,  0xE01EF,  "Mn", "异体字选择符补充（VS17-VS256）" },
};

/* ===================================================================
 * 辅助函数
 * =================================================================== */

/** 判断码点 cp 是否属于指定的特殊范围 */
static inline int UnicodeRangeContains(UnicodeSpecialRange id, uint32_t cp) {
    if (id >= UnicodeRangeCount) return 0;
    const UnicodeRangeEntry* e = &kUnicodeRanges[id];
    return cp >= e->start && cp <= e->end;
}

/**
 * 遍历查找码点 cp 所属的第一个特殊范围。
 * 返回枚举值，若未命中任何特殊范围则返回 (UnicodeSpecialRange)(-1)。
 */
static inline UnicodeSpecialRange UnicodeRangeLookup(uint32_t cp) {
    for (int i = 0; i < (int)UnicodeRangeCount; i++) {
        if (cp >= kUnicodeRanges[i].start && cp <= kUnicodeRanges[i].end)
            return (UnicodeSpecialRange)i;
    }
    return (UnicodeSpecialRange)(-1);
}

#ifdef __cplusplus
}
#endif

#endif /* UNICODE_SPECIAL_RANGES_H */