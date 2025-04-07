//
// Created by xiaoxianghui on 2024/1/31.
//

#ifndef DLX_H
#define DLX_H

/*
 * DLX算法(结构)思想
 * 此算法用于精确覆盖问题, 可通过以下例子了解
 * 在 2 * 2 矩阵中, 每行及每列都要有 1 - 2;
 * [1, 2] [2, 1]
 * [2, 1],[1, 2]
 * 显然, 仅有以上两种情况合法;
 * 转换为精确覆盖问题, 每填入一个数即为覆盖以下问题:
 * 1. 矩阵(0, 0) - (1, 1)是否为不为空.
 * 2. 行1 or 2 是否有 1 or 2.
 * 3. 列1 or 2 是否有 1 or 2.
 * 以上 4 * 3 个问题 化作 二进制矩阵 的 列,
 * 矩阵某一坐标的数字 化作 二进制矩阵 的 行.
 * 以上面提及的第一个合法矩阵为例, 化作 二进制矩阵 即为:
 * 1. [1, 0, 0, 0, |1, 0, 0, 0, |1, 0, 0, 0]
 * 2. [0, 1, 0, 0, |0, 1, 0, 0, |0, 0, 0, 1]
 * 3. [0, 0, 1, 0, |0, 0, 0, 1, |0, 1, 0, 0]
 * 4. [0, 0, 0, 1, |0, 0, 1, 0, |0, 0, 1, 0]
 * '|'是为了方便观察, 其中 行1 相关的行 有:
 * 1. [1, 0, 0, 0, |1, 0, 0, 0, |1, 0, 0, 0]
 *  . [1, 0, 0, 0, |0, 1, 0, 0, |0, 1, 0, 0] // 摒除 (0, 0) 为 2 的可能性
 *  . [0, 1, 0, 0, |1, 0, 0, 0, |0, 0, 1, 0] // 摒除 (0, 1) 为 1 的可能性
 *  . [0, 1, 0, 0, |0, 1, 0, 0, |0, 0, 0, 1] // (0, 1) 为 2 的可能性
 *  . [0, 0, 1, 0, |0, 0, 1, 0, |1, 0, 0, 0] // 摒除 (1, 0) 为 1 的可能性
 * 易得, 此问题的解的 二进制矩阵行序列 异或 的 结果 为 全为 1, 每两行 或运算 为 0
 * 显然, 矩阵中的 0 过多了, 空间复杂度过大, 故改用此结构, 仅对 为1的节点 进行操作
 */

#include <stdint.h>
#include <stdbool.h>
#include "oop.h"

#define className dlx

oopClassDeclare()

/**
 * @brief 创建 一个有 rowCount 行 colCount 列 的 dlx
 */
oopCreate(uint16_t rowCount, uint16_t colCount, uint16_t *result, uint16_t resultLen);

oopDestroy();

/**
 * @brief 在 rowId 行 colId 列 插入一个节点
 * @return 节点是否已存在
 */
oopPublic(bool, nodeAdd, uint16_t rowId, uint16_t colId);

/**
 * @brief 在 解空间 内 搜索 可行解
 * @param count 需要找到的解的个数
 * @return 找到的解的个数
 */
oopPublic(uint16_t, search, uint16_t count);

/**
 * @note 决策化作行
 * @note 状态化作列
 * @note 需要把 决策 及 决策对应的状态 映射成 行 和 列 并 插入dlx中
 * @note 得出解后再把解的行序列转换成实际解
 */
__attribute__((unused)) void dlxUsage(void);

#endif //DLX_H
