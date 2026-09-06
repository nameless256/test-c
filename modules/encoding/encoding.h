//
// Created by CodingDev on 2026/9/4.
//

#ifndef TEST_C_ENCODING_H
#define TEST_C_ENCODING_H

#include "def_enum.h"

#define enumName encoding_err
#define enumBase uint8_t
enumStart
    /* 成功 */
    enumEntry(None)                 // 成功
    /* 输入数据错误（解码侧） */
    enumEntry(Truncated)            // 不完整序列
    enumEntry(InvalidLead)          // 前导单元非法（UTF-8首字节错 / UTF-16高代理错）
    enumEntry(InvalidTrail)         // 后续单元非法（UTF-8续字节错 / UTF-16低代理错）
    enumEntry(Overlong)             // 过编码（Overlong），安全隐患
    enumEntry(Surrogate)            // 编码了代理对码点（U+D800-U+DFFF）
    enumEntry(OutOfRange)           // 码点超出 U+10FFFF
    /* 输入码点错误（编码侧） */
    enumEntry(InvalidCodepoint)     // 非法码点（代理对/超范围/保留区）
    /* 缓冲区错误（两类共有） */
    enumEntry(BufTooSmall)          // 输出缓冲区容量不足
    enumEntry(NullPtr)              // 输入或输出指针为 NULL
    /* 策略级错误（按需启用） */
    enumEntry(BomMisplaced)         // BOM 出现在非起始位置
    enumEntry(Reserved)             // 保留码点（如 U+FFFE/U+FFFF）
enumEnd

#include "clean_up_enum.h"

#endif //TEST_C_ENCODING_H
