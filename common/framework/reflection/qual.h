//
// Created by CodingDev on 2026/8/26.
//

#define enumName qual
#define enumBase uint8_t
enumStart
enumEntry(Null, 0b000)
enumEntry(Const, 0b001)
enumEntry(Volatile, 0b010)
enumEntry(Restrict, 0b100)
enumEnd

#include "clean_up_enum.h"
