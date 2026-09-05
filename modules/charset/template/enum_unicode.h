//
// Created by CodingDev on 2026/9/2.
//

#define enumName unicode
#define enumBase uint32_t
enumStart
    enumEntry(C0Control, 0x0000)        // C0 控制字符
    enumEntry(C1Control, 0x0080)        // C1 控制字符
    enumEntry(Surrogate, 0xD800)        // 代理区
    enumEntry(SurrogateHigh, 0xD800)    // 高代理对
    enumEntry(SurrogateLow, 0xDC00)     // 低代理对
    enumEntry(BmpPua, 0xE000)           // BMP 私用区（PUA）
    enumEntry(BmpNonchar, 0xFDD0)       // BMP 非字符
    enumEntry(Bom, 0xFEFF)              // BOM / 零宽不换行空格
    enumEntry(Replacement, 0xFFFD)      // 替换字符
    enumEntry(Nonchar, 0xFFFE)          // 结尾非字符
    enumEntry(Max, 0x10FFFF)            // 最大码点
enumEnd

#include "clean_up_enum.h"
