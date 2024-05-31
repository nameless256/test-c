//
// Created by xiaoxianghui on 2024/1/4.
//

#ifndef TEST_SUDOKU_H
#define TEST_SUDOKU_H

#include "list.h"
#include "dlx.h"

/**
 * 基本定义: 数独
 * 单元: 行, 列, 宫
 *
 * 基础解法: 唯一解法, 唯余解法
 * 唯一解法: 某单元内仅有该格可以填入某数
 * 唯余解法: 单格 候选数 个数为1 时 填入
 * 高阶解法: 根据其他方法辅助(如回溯法)唯一或唯余解法解题
 */

#ifndef BIT
#define BIT(n)                      (1UL << (n))
#endif

typedef enum {
    sudokuTag_Null = 0,
    sudokuTag_Clear = 0,
    sudokuTag_1 = BIT(0),
    sudokuTag_2 = BIT(1),
    sudokuTag_3 = BIT(2),
    sudokuTag_4 = BIT(3),
    sudokuTag_5 = BIT(4),
    sudokuTag_6 = BIT(5),
    sudokuTag_7 = BIT(6),
    sudokuTag_8 = BIT(7),
    sudokuTag_9 = BIT(8),
    sudokuTag_All = BIT(9) - 1,
} sudokuTag;

typedef enum {
    sudokuToken_Num,
    sudokuToken_Tag,
    sudokuToken_Fix,
} sudokuToken;

typedef enum {
    sudokuState_Null = 0,
    sudokuState_Related = BIT(0),
    sudokuState_Selected = BIT(1),
    sudokuState_Conflict = BIT(2),
    sudokuState_All = BIT(3) - 1,
} sudokuState;

typedef struct {
    sudokuTag data;
    sudokuToken token;
    sudokuState status;
} sudokuCell;

typedef struct {
    uint8_t x, y;
} sudokuCoord;

typedef struct {
    sudokuCoord coord;
    sudokuCell cell;
} sudokuCellInfo;

/*
 * 难度定义如下:
 * 入门: 空格在25个左右, 仅用唯一或唯余即可解决
 * 简单: 空格在35个左右, 仅用唯一(居多)或唯余即可解决
 * 中等: 空格在45个左右(35个左右的提示数), 仅用唯一或唯余(居多)即可解决
 * 困难: 空格在55个左右(25个左右的提示数), 需要使用进阶解法解决
 * 极端: 空格在55个左右(25个左右的提示数), 需要使用高阶解法解决
 */
typedef enum {
    sudokuLevel_Beginner,   ///< 入门: 空格在25个左右(56个左右的提示数), 仅用唯一或唯余即可解决
    sudokuLevel_Easy,       ///< 简单: 空格在35个左右(46个左右的提示数), 仅用唯一或唯余即可解决
    sudokuLevel_Medium,     ///< 中等: 空格在45个左右(36个左右的提示数), 仅用唯一或唯余即可解决
    sudokuLevel_Hard,       ///< 困难: 空格在55个左右(26个左右的提示数), 需要使用进阶解法解决
    sudokuLevel_Extreme,    ///< 极端: 空格在55个左右(26个左右的提示数), 需要使用高阶解法解决
    sudokuLevel_Max,
} sudokuLevel;

typedef struct {
    dlx *dlxObj; ///< 生成初盘, 生成题面, 状态检测
    listNode log;
    uint8_t final[9][9];
    sudokuCell grid[9][9];
    sudokuLevel level;
    sudokuCoord *coord; ///< 为空即未选中
    sudokuTag *input; ///< 为空即未选中
    sudokuTag operand; ///< sudokuState_Related 检查标记
    bool inputMode; ///< true 即为标记输入模式
    bool finish;
    uint8_t residue[10]; ///< 剩余数
    uint32_t timeStart;
    uint32_t timePause;
    uint32_t timeCost;
} sudoku;

uint8_t sudokuTag2Num(sudokuTag tag);

sudokuTag sudokuNum2Tag(uint8_t num);

uint8_t sudokuTagBinary1Count(sudokuTag tag);

bool sudokuIsFinish(sudoku *obj);

/******************************************************************/ // divLine

sudoku *sudokuCreate(sudokuLevel level);

void sudokuDestroy(sudoku **pObj);

bool sudokuSetCoord(sudoku *obj, sudokuCoord coord);

const sudokuCoord *sudokuGetCoord(sudoku *obj);

bool sudokuSetInputData(sudoku *obj, sudokuTag data);

const sudokuTag *sudokuGetInputData(sudoku *obj);

void sudokuSetInputMode(sudoku *obj, bool sign);

bool sudokuGetInputMode(sudoku *obj);

void sudokuRedo(sudoku *obj);

void sudokuHint(sudoku *obj);

void sudokuCancel(sudoku *obj);

void sudokuUsage(void);

#endif //TEST_SUDOKU_H
