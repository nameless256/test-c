//
// Created by xiaoxianghui on 2023/3/9.
//

#include "global_function.h"
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
    do {
        if (mkdir(copy)) {
            char *p = strrchr(copy, '/');
            if (!p) {
                perror("strrchr failed");
                break;
            }
            *p = '\0';
            pathDepth++;
        } else {
            pathDepth--;
            if (pathDepth) copy[strlen(copy)] = '/';
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
