//
// Created by xiaoxianghui on 2023/3/9.
//

#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BIT(n)                      (1UL << (n))
#define checkBit(arg, n)            (((arg) & BIT(n)) == BIT(n))
#define ARRAY_SIZE(array)           (sizeof(array) / sizeof((array)[0]))
#define MAX(a, b)                   ((a) > (b) ? (a) : (b))
#define MIN(a, b)                   ((a) < (b) ? (a) : (b))
#define ABS(a)                      ((0 - (a)) > 0 ? (-(a)) : (a))
#define SWAP(arg0, arg1)            do{(arg0) ^= (arg1); (arg1) ^= (arg0); (arg0) ^= (arg1);} while(0)
#define name2Str(name)              #name
#define nameVal2Str(name)           name2Str(name)
#define name2StrCase(name)          case name: return name2Str(name)
#define valMap(value, num, total) \
        ((total) ? (((value) > (total)) ? (num) : ((num) * (value) / (total))) : 0)
#define valMapRange(value, num, lBound, uBound) valMap(value - lBound, num, uBound - lBound)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define structOffsetOf(type, member) ((uintptr_t)(&((type *)0)->member))

#define containerOf(ptr, type, member) ((type *)((uintptr_t *)(ptr) - structOffsetOf(type, member)))

// 不可进行 break continue 操作
#define assertActions(action, expression, message, ...) \
        do {if (!(expression)) { fprintf(stderr, message, ##__VA_ARGS__); action;}} while (0)

#define assertReturns(expression, message, ...) \
        assertActions(return, expression, message, ##__VA_ARGS__)

#define autoReleaseBuffer(type, name, size) \
    for (type *name = (type *) malloc(sizeof(type) * size); name != NULL; free(name), name = NULL)

#define autoReleaseFile(name, path, args) \
    for (FILE *name = fopen(path, args); name != NULL; fclose(name), name = NULL)
    
#define enumValDef(name, init) name init,
#define enumValCapture(name, ...) name2StrCase(name);
#define enumIter(name, action) enumIter ## _ ## name(name, action)
#define enumDispatch(action, prefix, name, ...) action(prefix ## _ ## name, __VA_ARGS__)

#define enumDef(name) typedef enum { enumIter(name, enumValDef) } (name);
#define enumDefToStr(name) \
static inline char *toString ## _ ## name(name val) { \
    switch(val) { enumIter(name, enumValCapture) default: return "NaN"; } \
};

#define ALIAS(function)             __attribute__((alias(#function)))
#define WEAK                        __attribute__((weak))
#define UNUSED                      __attribute__((unused))
#define CLEANUP(function)           __attribute__((cleanup(function)))

uint8_t getNumDigit(uint32_t num);

/**
 * @brief 屏幕亮灭姿态检测
 * @details 设：坐标系O(xyz)中 屏幕朝右 为 +x, 屏幕朝前 为 +y, 屏幕垂直朝上 为 +z，且以下向量起点为原点
 * @details 向量 vS：水平垂直方向朝上，模长为 R
 * @details 向量 vX vY vZ 在数轴上 且为 vS 向量 分量
 * @details vS方向上的单位向量 终点坐标(x, y, z) 为 ((vX / R), (vY / R), (vZ / R))
 * @param[in] screenOn true 检测是否达到亮屏状态条件
 * @param[in] x,y,z (vX / R), (vY / R), (vZ / R)
 * @return 是否达到亮灭屏状态条件
 * @retval true 达到亮灭屏状态条件
 */
bool screenOnOffDetect(bool screenOn, double x, double y, double z);

double roundToNDecimalPlaces(double value, uint8_t n);

uint8_t hexChar2Num(char c);

/**
 * @brief MAC字符串转数字
 * @param[in] str MAC字符串，格式如下：xx:xx:xx:xx:xx:xx
 * @param[out] mac MAC转换成数字的输出地址
 * @return 转换是否成功
 * @retval true 失败
 */
bool macStr2Num(const char *str, uint64_t *mac);

char *macNum2Str(uint64_t macNum, char buf[]);

/**
 * @brief MAC地址自动划分
 * @param[in] argc
 * @param[in] argv
 * @return 0
 * @details
 * @code{.c}
 * int main(int argc, char *argv[]) {
 *     return macAddressAutoPartition(argc, argv);
 * }
 * @endcode
 *
 * <b>Example usage</b>
 * <li>.\\test.exe DC:71:DD:55:03:84 DC:71:DD:55:04:66 10 10 20</li>
 * @ingroup Main
 */
int macAddressAutoPartition(int argc, char *argv[]);

/**
 * 创建目录
 * @param path 目录的路径
 * @return 返回bool类型，表示操作是否成功
 */
bool createDir(const char *path);

void traverseDir(const char *dir, uint8_t depthMax, void (*cbFilePath)(const char *const filePath));

int isSubPath(const char *base_path, const char *path);

char *concatStrings(char separator, int count, ...);

bool checkLittleEndian();

void printByteAsHex(unsigned char byte);

bool printEscapes(unsigned char byte);

void printBuffer(const unsigned char *buff, size_t length);

#endif //GLOBAL_FUNCTION_H
