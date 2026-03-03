//
// Created by CodingDev on 2025/12/16.
//
#include "type_meta.h"

#define intName int8_t

#include "int_def_meta.h"

#define intName uint8_t

#include "int_def_meta.h"

#define intName int16_t

#include "int_def_meta.h"

#define intName uint16_t

#include "int_def_meta.h"

#define intName int32_t

#include "int_def_meta.h"

#define intName uint32_t

#include "int_def_meta.h"

#define intName int64_t

#include "int_def_meta.h"

#define intName uint64_t

#include "int_def_meta.h"

#define intName size_t

#include "int_def_meta.h"

#define enumName typeId
#define enumBase uint8_t
#define enumMember Bool, Int, Ptr, Enum, Float, Array, Union, Struct,

#include "enum_def_meta.h"

#define enumName qual
#define enumBase uint8_t
#define enumMember (Null, 0b000), (Const, 0b001), (Volatile, 0b010), (Restrict, 0b100),

#include "enum_def_meta.h"

#define enumName ptrTypeId
#define enumBase uint8_t
#define enumMember Type, Func, Array

#include "enum_def_meta.h"
