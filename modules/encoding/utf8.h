//
// Created by CodingDev on 2026/9/3.
//

#ifndef TEST_C_UTF8_H
#define TEST_C_UTF8_H

#include "unicode.h"
#include "encoding.h"

#define moduleName utf8

/**
 * @brief utf8单字符解码到unicode
 * @param[in] src 指向utf8字符串
 * @param[out] dst 指向unicode字符
 * @param[in] length utf8字符串可解析编码单元个数
 * @param[out] ofs 已解码utf8单字符编码单元个数
 * @return
 */
declare(encoding_err , decode, uint8_t *src, unicode *dst, uint8_t length, uint8_t *ofs);

/**
 * @brief unicode编码到utf8单字符
 * @param[in] src unicode码点
 * @param[out] dst 指向utf8字符串
 * @param[in] length utf8字符串可输出编码单元个数
 * @param[out] ofs 已编码utf8单字符编码单元个数
 * @return
 */
declare(encoding_err , encodeChar, unicode src, uint8_t *dst, uint8_t length, uint8_t *ofs);

declare(uint8_t, encode, unicode cp, uint8_t *const utf8, size_t utf8Length);

#undef moduleName

#endif //TEST_C_UTF8_H
