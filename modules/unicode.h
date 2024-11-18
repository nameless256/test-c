//
// Created by xiaoxianghui on 2024/11/15.
//

#ifndef TEST_C_UNICODE_H
#define TEST_C_UNICODE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define UNICODE_ERROR 0xFFFFFFFF
#define UNICODE_MAX 0x0010FFFF

/**
 * @param[in] utf8 传入读指针的地址 方便连续操作 指针会自动后移
 * @return unicode 码点
 * @retval UNICODE_ERROR 错误
 * @note 虽然错误码是 UNICODE_ERROR 但建议还是通过是否大于 UNICODE_MAX 判断是否为错误
 */
uint32_t unicodeGetCodePointByUtf8(const uint8_t **utf8);

/**
 * @param codePoint unicode 码点
 * @param[out] utf8 传入写指针的地址 方便连续操作 指针会自动后移
 * @param utf8Size 剩余缓冲区码元个数 (sizeof(buffer) / sizeof(uint8_t))
 * @return 是否成功
 * @retval true 失败
 */
bool unicodeSetUtf8ByCodePoint(uint32_t codePoint, uint8_t **utf8, size_t utf8Size);

/**
 * @param[in] utf16 传入读指针的地址 方便连续操作 指针会自动后移
 * @return unicode 码点
 * @retval UNICODE_ERROR 错误
 * @note 虽然错误码是 UNICODE_ERROR 但建议还是通过是否大于 UNICODE_MAX 判断是否为错误
 */
uint32_t unicodeGetCodePointByUtf16(const uint16_t **utf16);

/**
 * @param codePoint unicode 码点
 * @param[out] utf16 传入写指针的地址 方便连续操作 指针会自动后移
 * @param utf16Size 剩余缓冲区码元个数 (sizeof(buffer) / sizeof(uint16_t))
 * @return 是否成功
 * @retval true 失败
 */
bool unicodeSetUtf16ByCodePoint(uint32_t codePoint, uint16_t **utf16, size_t utf16Size);

/**
 * @param utf8 传入utf8码流
 * @param utf8Size utf8码流长度
 * @param utf16 utf16缓冲区
 * @param utf16Size utf16缓冲区大小 (码元个数)
 * @return 转换码元个数
 */
size_t unicodeUtf8ToUtf16(const uint8_t *utf8, size_t utf8Size, uint16_t *utf16, size_t utf16Size);

/**
 * @param utf16 传入utf16码流
 * @param utf16Size utf16码流长度
 * @param utf8 utf8缓冲区
 * @param utf8Size utf8缓冲区大小 (码元个数)
 * @return 转换码元个数
 */
size_t unicodeUtf16ToUtf8(const uint16_t *utf16, size_t utf16Size, uint8_t *utf8, size_t utf8Size);

#endif //TEST_C_UNICODE_H
