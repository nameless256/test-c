//
// Created by CodingDev on 2026/9/2.
//

#define enumName unicode_plane
#define enumBase uint8_t
enumStart
    enumEntry(BMP)      // 基本多文种平面
    enumEntry(SMP)      // 补充多文种平面
    enumEntry(SIP)      // 补充表意文字平面
    enumEntry(TIP)      // 第三表意文字平面
    // 4–13 未分配
    enumEntry(SSP, 14)  // 补充专用平面
    enumEntry(SPUA_A)   // 私用区平面 A
    enumEntry(SPUA_B)   // 私用区平面 B
enumEnd

#include "clean_up_enum.h"
