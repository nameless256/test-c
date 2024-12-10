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
 * @param utf8Length 剩余缓冲区码元个数
 * @retval true 失败
 */
bool unicodeSetUtf8ByCodePoint(uint32_t codePoint, uint8_t **utf8, size_t utf8Length);

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
 * @param utf16Length 剩余缓冲区码元个数
 * @retval true 失败
 */
bool unicodeSetUtf16ByCodePoint(uint32_t codePoint, uint16_t **utf16, size_t utf16Length);

/**
 * @param[in] utf8 传入utf8码流
 * @param utf8Length utf8码流长度
 * @param[out] utf16 utf16缓冲区
 * @param utf16Length utf16缓冲区大小 (码元个数)
 * @return 转换码元个数
 */
size_t unicodeUtf8ToUtf16(const uint8_t *utf8, size_t utf8Length, uint16_t *utf16, size_t utf16Length);

/**
 * @param[in] utf16 传入utf16码流
 * @param utf16Length utf16码流长度
 * @param[out] utf8 utf8缓冲区
 * @param utf8Length utf8缓冲区大小 (码元个数)
 * @return 转换码元个数
 */
size_t unicodeUtf16ToUtf8(const uint16_t *utf16, size_t utf16Length, uint8_t *utf8, size_t utf8Length);

/**
 * @param[in] utf8 传入utf8码流
 * @return utf8码元个数
 * @retval 0 失败
 */
size_t unicodeGetUtf8Length(const uint8_t *utf8);

/**
 * @param[in] utf16 传入utf16码流
 * @return utf16码元个数
 * @retval 0 失败
 */
size_t unicodeGetUtf16Length(const uint16_t *utf16);

/**
 * @param[in] utf16 传入utf16码流
 * @return utf8码元个数
 * @retval 0 失败
 */
size_t unicodeGetUtf8LengthByUtf16(const uint16_t *utf16);

/**
 * @param[in] utf8 传入utf8码流
 * @return utf16码元个数
 * @retval 0 失败
 */
size_t unicodeGetUtf16LengthByUtf8(const uint8_t *utf8);

/**
 * @param[in] utf16 传入utf16码流
 * @return utf8码流
 * @attention 需释放内存
 */
uint8_t *unicodeGetUtf8ByUtf16(const uint16_t *utf16);

/**
 * @param[in] utf8 传入utf8码流
 * @return utf16码流
 * @attention 需释放内存
 */
uint16_t *unicodeGetUtf16ByUtf8(const uint8_t *utf8);

enum utfBom {
    utfBom_None,
    utfBom_Utf8,
    utfBom_Utf16_LE,
    utfBom_Utf16_BE,
    utfBom_Utf32_LE,
    utfBom_Utf32_BE,
    utfBom_Max,
};

enum utfBom unicodeUtfCheckBom(const uint8_t *stream, size_t streamLength);

uint8_t unicodeUtfGetBomSize(enum utfBom bom);

uint8_t const *unicodeUtfGetBomBytes(enum utfBom bom);

void unicodeUsage(void);

#endif //TEST_C_UNICODE_H
