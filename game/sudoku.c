//
// Created by xiaoxianghui on 2024/1/4.
//

#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"

typedef struct {
    listNode entry;
    sudokuCellInfo info;
} sudokuLog;

static sudokuLog *logCreate(sudokuCoord coord, sudokuCell cell) {
    sudokuLog *obj = malloc(sizeof(sudokuLog));
    obj->entry = (listNode) listNodeInit(obj->entry);
    obj->info.coord = coord;
    obj->info.cell = cell;
    return obj;
}

static void logDestroy(sudokuLog *obj) {
    if (obj) free(obj);
}

static void statusUpdateRelated(sudoku *obj) {
    if (obj->coord) {
        if (obj->grid[obj->coord->y][obj->coord->x].token != sudokuToken_Tag)
            obj->operand = obj->grid[obj->coord->y][obj->coord->x].data;
    } else if (obj->input) {
        obj->operand = *obj->input;
    } else {
        obj->operand = sudokuTag_Null;
    }
    sudokuCoord coord;
    for (coord.y = 0; coord.y < 9; ++coord.y) {
        for (coord.x = 0; coord.x < 9; ++coord.x) {
            if (obj->grid[coord.y][coord.x].data & obj->operand) {
                obj->grid[coord.y][coord.x].status |= sudokuState_Related;
            } else {
                obj->grid[coord.y][coord.x].status &= ~sudokuState_Related;
            }
        }
    }
}

static void statusClear(sudoku *obj, sudokuState status) {
    sudokuCoord coord;
    for (coord.y = 0; coord.y < 9; ++coord.y)
        for (coord.x = 0; coord.x < 9; ++coord.x)
            obj->grid[coord.y][coord.x].status &= ~status;
}

static void gridStatusUpdate(sudoku *obj) {
    statusUpdateRelated(obj);
}

static bool checkFinal(sudoku *obj) {
    sudokuCoord coord;
    for (coord.y = 0; coord.y < 9; ++coord.y) {
        for (coord.x = 0; coord.x < 9; ++coord.x) {
            if (obj->grid[coord.y][coord.x].data == sudokuTag_Null) return false;
            if (obj->grid[coord.y][coord.x].status & sudokuState_Conflict) return false;
        }
    }
    return true;
}

static bool updateFinish(sudoku *obj) {
    obj->finish = checkFinal(obj);
    if (obj->coord) free(obj->coord);
    obj->coord = NULL;
    if (obj->input) free(obj->coord);
    obj->input = NULL;
    statusClear(obj, sudokuState_All);
    return true;
}

static bool setCell(sudoku *obj, sudokuCoord coord, sudokuTag data) {
    sudokuCell *editCell = &obj->grid[coord.y][coord.x];
    if (editCell->token == sudokuToken_Fix) return true;
    listAdd(&logCreate(coord, *editCell)->entry, &obj->log);
    sudokuToken inputToken = (obj->inputMode && data != sudokuTag_Clear) ? sudokuToken_Tag : sudokuToken_Num;
    if (inputToken == sudokuToken_Num || editCell->token != inputToken) {
        editCell->data = data;
    } else {
        editCell->data ^= data;
    }
    editCell->token = inputToken;
    return false;
}

static inline void statusSetSelected(sudoku *obj, sudokuCoord coord) {
    *obj->coord = coord;
    if (obj->grid[obj->coord->y][obj->coord->x].token == sudokuToken_Fix) return;
    obj->grid[obj->coord->y][obj->coord->x].status |= sudokuState_Selected;
}

static void gridBufShow(uint8_t (*gridBuf)[9]) {
    printf("+           +           +           +\n");
    for (uint8_t y = 0; y < 9; ++y) {
        for (uint8_t x = 0; x < 9; ++x) {
            if (x == 0) printf("  ");
            printf(" %c ", gridBuf[y][x] ? gridBuf[y][x] + '0' : '-');
            if (x == 2 || x == 5) printf(" | ");
            if (x == 8) printf("  \n");
        }
        if (y == 2 || y == 5)
            printf("+ ----------|-----------|---------- +\n");
    }
    printf("+           +           +           +\n");
}

static void sudokuGridShow(sudoku *obj) {
    uint8_t gridBuf[9][9] = {0};
    for (uint8_t y = 0; y < 9; ++y)
        for (uint8_t x = 0; x < 9; ++x) gridBuf[y][x] = sudokuTag2Num(obj->grid[y][x].data);
    gridBufShow(gridBuf);
}

static void dlxResult2GridBuf(const uint16_t *dlxResult, uint8_t (*gridBuf)[9]) {
    for (uint8_t i = 0; i < 81; ++i) {
        uint8_t x = (dlxResult[i] - 1) / 9 % 9;
        uint8_t y = (dlxResult[i] - 1) / 9 / 9;
        uint8_t n = (dlxResult[i] - 1) % 9 + 1;
        gridBuf[y][x] = n;
    }
}

static uint16_t cell2DlxRowId(uint8_t x, uint8_t y, uint8_t n) {
    return (y * 9 + x) * 9 + n;
}

static void cell2DlxColId(uint8_t x, uint8_t y, uint8_t n, uint16_t colId[4]) {
    /** (81) [  1,  81] */  // 第 col[0] [1, 81] 格内 是否有数值
    colId[0] = 1 + y * 9 + x;
    /** (81) [ 82, 162] */  // 第 y [0, 8] 行 内 是否有 n [1, 9]
    colId[1] = 1 + y * 9 + n + 80;
    /** (81) [163, 243] */  // 第 x [0, 8] 列 内 是否有 n [1, 9]
    colId[2] = 1 + x * 9 + n + 161;
    /** (81) [244, 324] */  // 第 (y / 3 * 3 + x / 3) [0, 8] 宫 内 是否有 n [1, 9]
    colId[3] = 1 + (y / 3 * 3 + x / 3) * 9 + n + 242;
}

static bool dlxAddCellCheckIllegal(dlx *obj, uint8_t x, uint8_t y, uint8_t n) {
    uint16_t colId[4] = {0};
    cell2DlxColId(x, y, n, colId);
    for (uint8_t i = 0; i < 4; ++i) if (!dlxColIsEmpty(obj, colId[i])) return true;
    uint16_t rowId = cell2DlxRowId(x, y, n);
    for (uint8_t i = 0; i < 4; ++i) dlxNodeAdd(obj, rowId, colId[i]);
    return false;
}

static void dlxAddCell(dlx *obj, uint8_t x, uint8_t y, uint8_t n) {
    uint16_t colId[4] = {0};
    cell2DlxColId(x, y, n, colId);
    uint16_t rowId = cell2DlxRowId(x, y, n);
    for (uint8_t i = 0; i < 4; ++i) dlxNodeAdd(obj, rowId, colId[i]);
}

static void dlxDelCell(dlx *obj, uint8_t x, uint8_t y, uint8_t n) {
    dlxRowDel(obj, cell2DlxRowId(x, y, n));
}

static void dlxAddCellByTag(dlx *obj, uint8_t x, uint8_t y, sudokuTag tag) {
    for (uint8_t i = 0; i < 9; ++i) if (tag & BIT(i)) dlxAddCell(obj, x, y, i + 1);
}

static void dlxDelCellByTag(dlx *obj, uint8_t x, uint8_t y, sudokuTag tag) {
    for (uint8_t i = 0; i < 9; ++i) if (tag & BIT(i)) dlxDelCell(obj, x, y, i + 1);
}

#define SUDOKU_DLX_ROW_COUNT 729 /// 81 cells * 9 numbers
#define SUDOKU_DLX_COL_COUNT 324 /// 81 cells + 3 unit(9 row + 9 col + 9 box) * 9 * 9 numbers

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array)           (sizeof(array) / sizeof((array)[0]))
#endif

static bool sudokuGenerateFinal(sudoku *obj) {
    uint16_t result[81] = {0};
    uint8_t gridBuf[9][9] = {0};
    obj->dlxObj = dlxCreate(SUDOKU_DLX_ROW_COUNT, SUDOKU_DLX_COL_COUNT, result, ARRAY_SIZE(result));
    uint8_t count = 11; // 11个数概率最大
    while (count) {
        uint8_t x = rand() % 9, y = rand() % 9, n = rand() % 9 + 1;
        if (dlxAddCellCheckIllegal(obj->dlxObj, x, y, n)) continue;
        gridBuf[y][x] = n, count--;
    }
    for (uint8_t y = 0; y < 9; ++y) {
        for (uint8_t x = 0; x < 9; ++x) {
            if (gridBuf[y][x]) continue;
            dlxAddCellByTag(obj->dlxObj, x, y, sudokuTag_All);
        }
    }
    bool reVal = true;
    if (dlxSearch(obj->dlxObj, 1)) {
        dlxResult2GridBuf(result, obj->final);
        gridBufShow(obj->final);
        reVal = false;
    }
    dlxDestroy(&obj->dlxObj);
    return reVal;
}

static uint8_t numOfSpaces[sudokuLevel_Max] = {
    [sudokuLevel_Beginner] = 25,
    [sudokuLevel_Easy] = 35,
    [sudokuLevel_Medium] = 45,
    [sudokuLevel_Hard] = 55,
    [sudokuLevel_Extreme] = 0xff,
};

static void sudokuGenerate(sudoku *obj, sudokuLevel level) {
    uint8_t gridBuf[9][9] = {0};
    memcpy(gridBuf, obj->final, 81);
    obj->dlxObj = dlxCreate(SUDOKU_DLX_ROW_COUNT, SUDOKU_DLX_COL_COUNT, NULL, 81);
    for (uint8_t y = 0; y < 9; ++y) {
        for (uint8_t x = 0; x < 9; ++x) {
            dlxAddCell(obj->dlxObj, x, y, gridBuf[y][x]);
        }
    }
    uint8_t count = numOfSpaces[level];
    uint8_t failCount = 0, lastCount = count;
    while (count > 0) {
        if (count == lastCount) failCount++;
        if (failCount > 200) break;
        uint8_t x = rand() % 9, y = rand() % 9;
        if (!gridBuf[y][x]) continue;
        dlxAddCellByTag(obj->dlxObj, x, y, sudokuTag_All & ~sudokuNum2Tag(gridBuf[y][x]));
        if (dlxSearch(obj->dlxObj, 2) == 1) gridBuf[y][x] = 0, count--;
        else dlxDelCellByTag(obj->dlxObj, x, y, sudokuTag_All & ~sudokuNum2Tag(gridBuf[y][x]));
        lastCount = count;
    }
    uint8_t holeCount = numOfSpaces[level] - count;
    printf("[%d] --------- {%s} %d : %d \n", __LINE__, __FUNCTION__, holeCount, 81 - holeCount);
    gridBufShow(gridBuf);
    for (uint8_t y = 0; y < 9; ++y) {
        for (uint8_t x = 0; x < 9; ++x) {
            obj->grid[y][x].data = sudokuNum2Tag(gridBuf[y][x]);
            if (obj->grid[y][x].data) obj->grid[y][x].token = sudokuToken_Fix;
        }
    }
    dlxDestroy(&obj->dlxObj);
}

static void resetRandomSeed() {
    uint32_t seed = (unsigned) time(NULL);
    printf("[%d] --------- {%s} seed %u \n", __LINE__, __FUNCTION__, seed);
    srand(seed); // 重设随机种子, 用于生成数独
}

sudoku *sudokuCreate(sudokuLevel level) {
    sudoku *obj = malloc(sizeof(sudoku));
    memset(obj, 0, sizeof(sudoku));
    obj->log = (listNode) listNodeInit(obj->log);
    obj->level = level;
    resetRandomSeed();
    while (sudokuGenerateFinal(obj));
    sudokuGenerate(obj, level);
    return obj;
}

void sudokuDestroy(sudoku **pObj) {
    if (*pObj == NULL) return;
//    dlxDestroy(&(*pObj)->dlxObj);
    while (!listIsEmpty(&(*pObj)->log)) logDestroy(containerOf(listDel((*pObj)->log.next), sudokuLog, entry));
    if ((*pObj)->coord) free((*pObj)->coord);
    (*pObj)->coord = NULL;
    if ((*pObj)->input) free((*pObj)->coord);
    (*pObj)->input = NULL;
    free(*pObj);
    *pObj = NULL;
}

sudoku *sudokuLoad(const char *filePath) {
/// \todo 数独的加载
    return NULL;
}

void sudokuSave(sudoku *obj, const char *filePath) {
/// \todo 数独的保存
}

#define sudokuTagMapCase(num) case sudokuTag_##num: reVal = num; break

uint8_t sudokuTag2Num(sudokuTag tag) {
    uint8_t reVal = 0;
    switch (tag) {
        sudokuTagMapCase(1);
        sudokuTagMapCase(2);
        sudokuTagMapCase(3);
        sudokuTagMapCase(4);
        sudokuTagMapCase(5);
        sudokuTagMapCase(6);
        sudokuTagMapCase(7);
        sudokuTagMapCase(8);
        sudokuTagMapCase(9);
        default:
            break;
    }
    return reVal;
}

sudokuTag sudokuNum2Tag(uint8_t num) {
    if (num <= 0 || 10 <= num) return sudokuTag_Null;
    return BIT(num - 1);
}

uint8_t sudokuTagBinary1Count(sudokuTag tag) {
    if (sudokuTag2Num(tag)) return 1;
    uint8_t reVal = 0;
    for (uint8_t i = 0; i < 9; ++i) if (tag & BIT(i)) reVal++;
    return reVal;
}

bool sudokuSetCoord(sudoku *obj, sudokuCoord coord) {
    if (obj->finish) return true;
    if (obj->input) {
        setCell(obj, coord, *obj->input);
        gridStatusUpdate(obj);
        updateFinish(obj);
        return false;
    }
    if (obj->coord) {
        obj->grid[obj->coord->y][obj->coord->x].status &= ~sudokuState_Selected;
        if (obj->coord->x == coord.x && obj->coord->y == coord.y) {
            free(obj->coord);
            obj->coord = NULL;
        } else {
            statusSetSelected(obj, coord);
        }
    } else {
        obj->coord = malloc(sizeof(sudokuCoord));
        statusSetSelected(obj, coord);
    }
    gridStatusUpdate(obj);
    return false;
}

const sudokuCoord *sudokuGetCoord(sudoku *obj) {
    return obj->coord;
}

bool sudokuSetInputData(sudoku *obj, sudokuTag data) {
    if (obj->finish) return true;
    if (obj->coord) {
        setCell(obj, *obj->coord, data);
        gridStatusUpdate(obj);
        updateFinish(obj);
        return false;
    }
    if (obj->input) {
        if (*obj->input == data) {
            free(obj->input);
            obj->input = NULL;
        } else {
            *obj->input = data;
        }
    } else {
        obj->input = malloc(sizeof(sudokuTag));
        *obj->input = data;
    }
    gridStatusUpdate(obj);
    return false;
}

const sudokuTag *sudokuGetInputData(sudoku *obj) {
    return obj->input;
}

void sudokuSetInputMode(sudoku *obj, bool sign) {
    if (obj->finish) return;
    obj->inputMode = sign;
}

bool sudokuGetInputMode(sudoku *obj) {
    return obj->inputMode;
}

void sudokuRedo(sudoku *obj) {
    if (obj->finish) return;
    while (!listIsEmpty(&obj->log)) logDestroy(containerOf(listDel(obj->log.next), sudokuLog, entry));
    if (obj->coord) free(obj->coord);
    obj->coord = NULL;
    if (obj->input) free(obj->coord);
    obj->input = NULL;
    sudokuCoord coord;
    for (coord.y = 0; coord.y < 9; ++coord.y) {
        for (coord.x = 0; coord.x < 9; ++coord.x) {
            sudokuCell *editCell = &obj->grid[coord.y][coord.x];
            editCell->status = sudokuState_Null;
            if (editCell->token == sudokuToken_Fix) continue;
            editCell->data = sudokuTag_Null;
            editCell->token = sudokuToken_Num;
        }
    }
}

void sudokuHint(sudoku *obj) {
    if (obj->finish) return;
    /// \todo 检查冲突提示
    /// \todo 已填入数与答案不一提示
    /// \todo 唯一法提示
    /// \todo 唯余法提示
    /// \todo 依据答案随机空格提示
}

void sudokuCancel(sudoku *obj) {
    if (obj->finish) return;
    if (listIsEmpty(&obj->log)) return;
    sudokuLog *log = containerOf(obj->log.next, sudokuLog, entry);
    obj->grid[log->info.coord.y][log->info.coord.x] = log->info.cell;
    gridStatusUpdate(obj);
    listDel(&log->entry);
    logDestroy(log);
}

bool sudokuIsFinish(sudoku *obj) {
    return obj->finish;
}

void sudokuUsage(void) {
    // 30ms
    sudokuDestroy(&(sudoku *) {sudokuCreate(sudokuLevel_Extreme)});
}
