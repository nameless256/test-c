//
// Created by CodingDev on 2026/9/2.
//

#define enumName unicode_size
#define enumBase uint16_t
enumStart
    enumEntry(Plane, 0x10000)       // 平面
    enumEntry(C0Control, 0x20)      // C0 控制字符
    enumEntry(C1Control, 0x20)      // C1 控制字符
    enumEntry(Surrogate, 0x800)     // 代理区
    enumEntry(SurrogatePair, 0x400) // 代理对
    enumEntry(BmpPua, 0x1900)       // BMP 私用区（PUA）
    enumEntry(BmpNonchar, 0x20)     // BMP 非字符
    enumEntry(Nonchar, 0x2)         // 结尾非字符
enumEnd

#include "clean_up_enum.h"
