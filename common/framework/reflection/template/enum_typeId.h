//
// Created by CodingDev on 2026/8/26.
//

#define enumName typeId
#define enumBase uint8_t
enumStart
    enumEntry(Bool)
    enumEntry(Int)
    enumEntry(Ptr)
    enumEntry(Enum)
    enumEntry(Float)
    enumEntry(Array)
    enumEntry(Union)
    enumEntry(Struct)
    enumEntry(Class)
enumEnd

#include "clean_up_enum.h"
