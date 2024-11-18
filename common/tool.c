//
// Created by xiaoxianghui on 2023/3/9.
//

#include "tool.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t getNumDigit(uint32_t num) {
    return 1 + (uint8_t) log10(num);
}

bool screenOnOffDetect(bool screenOn, double x, double y, double z) {
    double aX = asin(z / sqrt(x * x + z * z)) * 180 / M_PI; /**< 向量 (vX + vZ) 在 xz平面 上 与 xy平面 的 夹角 */
    double aY = asin(y / sqrt(y * y + z * z)) * 180 / M_PI; /**< 向量 (vY + vZ) 在 yz平面 上 与 xz平面 的 夹角 */
    double aZ = z > 0 ? (90 - fabs(aY)) : -(90 - fabs(aY)); /**< 向量 (vY + vZ) 在 yz平面 上 与 xy平面 的 夹角 */
    if (fabs(aX) > 45 && (aY <= -40 || aZ > 50)) {
        return screenOn;
    } else if (fabs(aX) < 40 || aZ < 45) {
        return !screenOn;
    }
    return false;
}

double roundToNDecimalPlaces(double value, uint8_t n) {
    double weight = pow(10, n);
    return round(value * weight) / weight;
}

uint8_t hexChar2Num(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'f') return c - 'a' + 0x0a;
    else if ('A' <= c && c <= 'F') return c - 'A' + 0x0A;
    else return -1;
}

bool macStr2Num(const char *str, uint64_t *mac) {
    *mac = 0;
    for (int i = 0; i < 6; ++i) {
        *mac <<= 8;
        uint8_t num = hexChar2Num(str[i << 1]);
        if (num < 0) return true;
        *mac |= num << 4;
        num = hexChar2Num(str[(i << 1) + 1]);
        if (num < 0) return true;
        *mac |= num;
        str++;
    }
    return false;
}

char *macNum2Str(uint64_t macNum, char buf[]) {
    uint8_t mac[6] = {
        macNum >> (5 << 3), macNum >> (4 << 3), macNum >> (3 << 3),
        macNum >> (2 << 3), macNum >> (1 << 3), macNum >> (0 << 3),
    };
    sprintf(buf, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buf;
}

int macAddressAutoPartition(int argc, char **argv) {
    if (argc >= 4) {
        uint64_t mac[2];
        uint64_t macSection[argc - 3][2];
        if (macStr2Num(argv[1], &mac[0]) || macStr2Num(argv[2], &mac[1])) goto errParse;
        for (int i = 0; i < argc - 3; ++i) {
            macSection[i][0] = i ? macSection[i - 1][1] + 1 : mac[0];
            int macCount = (int) strtod(argv[3 + i], NULL);
            if (macCount < 1) goto errParse;
            macSection[i][1] = macSection[i][0] + macCount - 1;
            char buf[2][6 * 2 + 5 + 1]; // 6 Byte + 5 * ':' + 1 * "" == 6 * 2 + 5 + 1 == 18
            macNum2Str(macSection[i][0], buf[0]);
            macNum2Str(macSection[i][1], buf[1]);
            printf(" %d:[%s ~ %s] \n", macCount, buf[0], buf[1]);
        }
        goto endParse;
    }
    errParse:
    printf("err\n");
    endParse:
    system("pause");
    return 0;
}

#include <io.h>

bool createDir(const char *const path) {
    char *copy = calloc(strlen(path) + 1, 1);
    if (copy == NULL) return true;
    strcpy(copy, path);
    uint8_t pathDepth = 1;
    if ((strrchr(copy, '.') && strrchr(copy, '\\') && (strrchr(copy, '\\') < strrchr(copy, '.')))) {
        *strrchr(copy, '\\') = '\0';
    }
    do {
        if (access(copy, F_OK) || mkdir(copy)) {
            char *p = strrchr(copy, '\\');
            if (!p) {
                perror("strrchr failed");
                break;
            }
            *p = '\0';
            pathDepth++;
        } else {
            pathDepth--;
            if (pathDepth) copy[strlen(copy)] = '\\';
        }
        if (pathDepth > 16) {
            perror("path depth too big");
            break;
        }
    } while (pathDepth);
    free(copy), copy = NULL;
    if (pathDepth) return true;
    return false;
}

#include <windows.h>

static void traverseDir1(char *dir, uint16_t bufLen, uint8_t depth, uint8_t depthMax,
                         void (*cbFilePath)(const char *const filePath)) {
    assertReturns(dir, "dir is null\n");
    assertReturns(depth <= depthMax, "dir traversal depth is too large\n");
    assertReturns(bufLen >= strlen(dir) + strlen("\\*"), "path too long\n");
    strcat(dir, "\\*");
    HANDLE hFind;
    WIN32_FIND_DATA ffd;
    hFind = FindFirstFile(dir, &ffd);
    assertActions(goto dirReset, hFind != INVALID_HANDLE_VALUE,
                  "unable to open directory, error code: %lu\n", GetLastError());
    do {
        if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, "..")) continue;
/*
        printf("ATTR 0x%08lx", ffd.dwFileAttributes);
        for (int i = 0; i < depth; ++i) printf(" |  ");
        printf(" |- %s\n", ffd.cFileName);
*/
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char *filePath = calloc(strlen(dir) + strlen(ffd.cFileName), sizeof(char));
            if (!filePath) {
                printf("file path malloc failed\n");
            } else {
                strcpy(filePath, dir);
                strcpy(strrchr(filePath, '*'), ffd.cFileName);
                if (cbFilePath) cbFilePath(filePath);
                free(filePath), filePath = NULL;
            }
        } else {
            if (strlen(dir) + strlen(ffd.cFileName) > bufLen) {
                printf("path too long\n");
            } else {
                strcpy(strrchr(dir, '*'), ffd.cFileName);
                traverseDir1(dir, bufLen, depth + 1, depthMax, cbFilePath);
                memset(strrchr(dir, '\\'), 0, strlen(ffd.cFileName));
                strcat(dir, "\\*");
            }
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
    dirReset:
    memset(strrchr(dir, '\\'), 0, strlen("\\*"));
}

void traverseDir(const char *const dir, uint8_t depthMax, void (*cbFilePath)(const char *const filePath)) {
    assertReturns(dir, "dir is null\n");
    uint16_t bufLen = MAX_PATH;
    char *dirCopy = calloc(bufLen, sizeof(char));
    assertReturns(dirCopy, "dirCopy malloc failed\n");
    strcpy(dirCopy, dir);
    traverseDir1(dirCopy, bufLen, 0, depthMax, cbFilePath);
    free(dirCopy), dirCopy = NULL;
}

// 判断 path 是否在 base_path 下
int isSubPath(const char *base_path, const char *path) {
    size_t base_len = strlen(base_path);
    size_t path_len = strlen(path);
    // 如果 base_path 比 path 长，不可能是子路径
    if (base_len > path_len) return 0;
    // 比较前缀是否相同
    if (strncmp(base_path, path, base_len) != 0) return 0;
    // 检查 base_path 后是否有路径分隔符
    if (path[base_len] == '/' || path[base_len] == '\\') return 1;
    // 检查 base_path 是否正好是 path 的前缀
    return (path[base_len] == '\0');
}

// 拼接字符串的函数实现
char *concatStrings(char separator, int count, ...) {
    // 初始化可变参数列表
    va_list args;
    va_start(args, count);
    // 计算总长度
    size_t totalLength = 0;
    for (int i = 0; i < count; ++i) {
        const char *str = va_arg(args, const char*);
        totalLength += strlen(str);
    }
    totalLength += count - 1;  // 添加分隔符的长度
    // 分配内存
    char *buffer = (char *) malloc(totalLength + 1);  // +1 是为了添加空字符 '\0'
    assertActions(goto argsRelease, buffer != NULL, "Memory allocation failed\n");
    va_start(args, count);
    // 拼接字符串
    char *dest = buffer;
    for (int i = 0; i < count; ++i) {
        const char *str = va_arg(args, const char*);
        dest += sprintf(dest, "%s", str);
        // 不在最后一个字符串后面添加分隔符
        if (i != count - 1 && separator != '\0') *dest++ = separator;
    }
    // 确保以空字符结尾
    *dest = '\0';
    // 结束可变参数列表
    argsRelease:
    va_end(args);
    return buffer;
}

// 返回处理 utf16 代码单元 个数
uint8_t utf16ToUtf8(const uint16_t *utf16, uint8_t *utf8) {
    if (utf16 == NULL || utf8 == NULL) return 0;
    uint32_t codePoint = *utf16;
    bool isSurrogate = false;
    if (codePoint >= 0xD800 && codePoint <= 0xDBFF) { // 高代理对
        uint16_t lowSurrogate = *(utf16 + 1);
        if (lowSurrogate >= 0xDC00 && lowSurrogate <= 0xDFFF) { // 低代理对
            codePoint = 0x10000 + ((codePoint - 0xD800) << 10) + (lowSurrogate - 0xDC00);
            isSurrogate = true;
        } else {
            // 无效的代理对，处理错误
            return 0;
        }
    }
    uint8_t length = 0;
    if (codePoint <= 0x7F) {
        utf8[length++] = (uint8_t) (codePoint);
    } else if (codePoint <= 0x7FF) {
        utf8[length++] = (uint8_t) ((codePoint >> 6) | 0xC0);
        utf8[length++] = (uint8_t) ((codePoint & 0x3F) | 0x80);
    } else if (codePoint <= 0xFFFF) {
        utf8[length++] = (uint8_t) ((codePoint >> 12) | 0xE0);
        utf8[length++] = (uint8_t) (((codePoint >> 6) & 0x3F) | 0x80);
        utf8[length++] = (uint8_t) ((codePoint & 0x3F) | 0x80);
    } else if (codePoint <= 0x10FFFF) {
        utf8[length++] = (uint8_t) ((codePoint >> 18) | 0xF0);
        utf8[length++] = (uint8_t) (((codePoint >> 12) & 0x3F) | 0x80);
        utf8[length++] = (uint8_t) (((codePoint >> 6) & 0x3F) | 0x80);
        utf8[length++] = (uint8_t) ((codePoint & 0x3F) | 0x80);
    } else {
        // 无效的代码点，处理错误
        return 0;
    }
    utf8[length] = '\0';
    return isSurrogate ? 2 : 1;
}

// 判断字节序的函数
int checkEndianness() {
    uint32_t num = 0x12345678;
    uint8_t *ptr = (uint8_t *)&num;

    if (*ptr == 0x12) {
        return 1; // Big-Endian
    } else if (*ptr == 0x78) {
        return 0; // Little-Endian
    } else {
        return -1; // Unknown Endianness
    }
}

void print_byte_as_hex(unsigned char byte) {
    // 高4位
    unsigned char high_nibble = (byte >> 4) & 0x0F;
    // 低4位
    unsigned char low_nibble = byte & 0x0F;

    // 将高4位转换为16进制字符
    putchar(high_nibble < 10 ? '0' + high_nibble : 'A' + high_nibble - 10);
    // 将低4位转换为16进制字符
    putchar(low_nibble < 10 ? '0' + low_nibble : 'A' + low_nibble - 10);
}

#include <ctype.h>

void print_buffer(const unsigned char *buff, size_t length) {
    for (size_t i = 0; i < length; i++) {
        print_byte_as_hex(buff[i]);
/*
        if (isprint(buff[i])) {
            putchar(buff[i]);
        } else {
            if (buff[i]) print_byte_as_hex(buff[i]);
            else putchar(' ');
        }
*/
        putchar(' ');
        if (i % 16 == 0 && i != 0) {
            putchar('\n');
        }
    }
    putchar('\n');
}
