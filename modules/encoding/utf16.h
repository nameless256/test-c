//
// Created by Admin on 26-9-6.
//

#ifndef TEST_C_UTF16_H
#define TEST_C_UTF16_H

#include "unicode.h"
#include "encoding.h"

#define moduleName utf16

/**
 * @brief utf16单字符解码到unicode
 * @param[in] src 指向utf16字符串
 * @param[out] dst 指向unicode字符
 * @param[in] length utf16字符串可解析编码单元个数
 * @param[out] ofs 已解码utf16单字符编码单元个数
 * @return
 */
declare(encoding_err, decode, uint16_t *src, unicode *dst, uint8_t length, uint8_t *ofs);

/**
 * @brief unicode编码到utf16单字符
 * @param[in] src unicode码点
 * @param[out] dst 指向utf16字符串
 * @param[in] length utf16字符串可输出编码单元个数
 * @param[out] ofs 已编码utf16单字符编码单元个数
 * @return
 */
declare(encoding_err, encode, unicode src, uint16_t *dst, uint8_t length, uint8_t *ofs);

#undef moduleName

#endif //TEST_C_UTF16_H
