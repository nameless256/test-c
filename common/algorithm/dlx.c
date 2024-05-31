//
// Created by xiaoxianghui on 2024/1/31.
//

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "dlx.h"

/// 指针操作宏定义
#define dlxNodeVHide(node) (node)->up->down = (node)->down, (node)->down->up = (node)->up
#define dlxNodeHHide(node) (node)->left->right = (node)->right, (node)->right->left = (node)->left
#define dlxNodeVShow(node) (node)->up->down = (node), (node)->down->up = (node)
#define dlxNodeHShow(node) (node)->left->right = (node), (node)->right->left = (node)
#define dlxIsEmptyV(node) ((node)->up == (node) && (node)->down == (node))
#define dlxIsEmptyH(node) ((node)->left == (node) && (node)->right == (node))
#define dlxNodeInit(node) (node)->up = (node)->down = (node)->left = (node)->right = (node)

static void dlxNodeHInsert(dlxNode *node, dlxNode *head) {
    node->left = head, node->right = head->right;
    dlxNodeHShow(node);
}

static void dlxNodeVInsert(dlxNode *node, dlxNode *head) {
    node->up = head, node->down = head->down;
    dlxNodeVShow(node);
}

static dlxNode *dlxNodeRemove(dlxNode *node) {
    dlxNodeHHide(node), dlxNodeVHide(node), dlxNodeInit(node);
    node->col->size--, node->col = NULL, node->rowId = 0;
    return node;
}

void dlxHide(dlxCol *col) {
    dlxCursor r, c;
    dlxNodeHHide(&col->node);
    for (r = col->node.down; r != &col->node; r = r->down)
        for (c = r->right; c != r; c = c->right) dlxNodeVHide(c), --(c->col->size);
}

void dlxShow(dlxCol *col) {
    dlxCursor r, c;
    for (r = col->node.down; r != &col->node; r = r->down)
        for (c = r->right; c != r; c = c->right) dlxNodeVShow(c), ++(c->col->size);
    dlxNodeHShow(&col->node);
}

dlx *dlxCreate(uint16_t rowCount, uint16_t colCount, uint16_t *result, uint16_t resultLen) {
    dlx *obj = malloc(sizeof(dlx)); // 基本结构 空间分配
    obj->colCount = colCount + 1; // + 1: 行首
    obj->rowCount = rowCount + 1; // + 1: 列首
    obj->result = result, obj->resultLen = resultLen;
    obj->stack = calloc(obj->resultLen, sizeof(uint16_t));
    obj->col = malloc(obj->colCount * sizeof(dlxCol));
    // 列首节点数组 初始化
    for (uint16_t i = 0; i < obj->colCount; ++i) {
        dlxNodeInit(&obj->col[i].node);
        obj->col[i].node.rowId = 0, obj->col[i].node.col = &obj->col[i];
        obj->col[i].size = 0, obj->col[i].id = i; // 标记第几列
    }
    // 按 列首节点数组顺序 依次链接 生成 列首链表
    for (uint16_t i = 0; i < colCount; ++i)
        dlxNodeHInsert(&obj->col[(i + 1) % obj->colCount].node, &obj->col[i].node);
    obj->first = (dlxCursor *) calloc(obj->rowCount, sizeof(dlxCursor)); // + 1: 列首; 指针初始化 为 0
    obj->first[0] = &obj->col[0].node; // first[0] 指向首行 即 列首
    return obj;
}

void dlxDestroy(dlx **pObj) {
    if (*pObj == NULL) return;
    for (uint16_t i = 0; i < (*pObj)->colCount; ++i) // 销毁 列首 的 垂直链表
        while (!dlxIsEmptyV(&(*pObj)->col[i].node)) free(dlxNodeRemove((*pObj)->col[i].node.down));
    free((*pObj)->stack), free((*pObj)->first), free((*pObj)->col), free(*pObj);
    *pObj = NULL;
}

bool dlxNodeAdd(dlx *obj, uint16_t rowId, uint16_t colId) {
    // 确保不会有重复节点
    for (dlxCursor i = obj->col[colId].node.down; i != &obj->col[colId].node; i = i->down)
        if (i->rowId == rowId) return true;
    // 节点创建
    dlxNode *node = malloc(sizeof(dlxNode));
    node->rowId = rowId, node->col = &obj->col[colId], node->col->size++;
    dlxNodeVInsert(node, &obj->col[colId].node);
    if (obj->first[rowId]) dlxNodeHInsert(node, obj->first[rowId]);
    else obj->first[rowId] = node->left = node->right = node; // 如果当前行为空则直接插入
    return false;
}

void dlxRowDel(dlx *obj, uint16_t rowId) {
    while (obj->first[rowId]) {
        dlxNode *node = obj->first[rowId];
        if (node->right == node) obj->first[rowId] = NULL;
        else obj->first[rowId] = node->right;
        free(dlxNodeRemove(node));
    }
}

void dlxColDelRow(dlx *obj, uint16_t colId) {
    while (!dlxIsEmptyV(&obj->col[colId].node)) dlxRowDel(obj, obj->col[colId].node.down->rowId);
}

dlxCol *dlxGetMinCol(dlx *obj) {
    dlxNode *minCol = obj->col[0].node.right;
    for (dlxCursor i = minCol; i != &obj->col[0].node; i = i->right)
        if (i->col->size < minCol->col->size) minCol = i;
    return minCol->col;
}

uint16_t dlxGetColSizeById(dlx *obj, uint16_t colId) {
    return obj->col[colId].size;
}

bool dlxColIsEmpty(dlx *obj, uint16_t colNum) {
    return dlxIsEmptyV(&obj->col[colNum].node);
}

bool dlxIsEmpty(dlx *obj) {
    return dlxIsEmptyH(&obj->col[0].node);
}

static uint16_t dlxDance(dlx *obj, uint16_t idx, uint16_t count) {
    uint16_t resultCount = 0; // 0: 无解
    if (dlxIsEmpty(obj)) { // 有解
        if (obj->result != NULL) {
            memset(obj->result, 0, obj->resultLen * sizeof(uint16_t));
            memcpy(obj->result, obj->stack, obj->resultLen * sizeof(uint16_t));
        }
        return 1;
    } else if (idx >= obj->resultLen) {
        printf("[%d] --------- {%s} not enough results cached ! \n", __LINE__, __FUNCTION__);
        return 0;
    }
    dlxCol *minCol = dlxGetMinCol(obj);
    dlxHide(minCol);
    dlxCursor r, c;
    for (r = minCol->node.down; r != &minCol->node; r = r->down) {
        for (c = r->right; c != r; c = c->right) dlxHide(c->col);
        obj->stack[idx] = r->rowId; // 按递归调用顺序依次记录解的行号
        resultCount += dlxDance(obj, idx + 1, count);
        for (c = r->left; c != r; c = c->left) dlxShow(c->col);
        if (count == resultCount) break; // 需要的解都已找到
    }
    dlxShow(minCol);
    return resultCount; // 无解返回0并在下一分支搜索解
}

uint16_t dlxSearch(dlx *obj, uint16_t count) {
    return dlxDance(obj, 0, count);
}

__attribute__((unused))
void dlxUsage() {
#define ROW_COUNT 6
#define COL_COUNT 7
    uint8_t matrix[ROW_COUNT][COL_COUNT] = {
        {0, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 1},
    };
    uint16_t result[ROW_COUNT] = {0};
    dlx *obj = dlxCreate(ROW_COUNT, COL_COUNT, result, ROW_COUNT);
    for (int y = 0; y < ROW_COUNT; ++y)
        for (int x = 0; x < COL_COUNT; ++x) if (matrix[y][x]) dlxNodeAdd(obj, y + 1, x + 1);
    if (dlxSearch(obj, 2)) {
        for (int i = 0; result[i]; ++i)
            printf("[%d] --------- {%s} %d \n", __LINE__, __FUNCTION__, result[i]);
    } else {
        printf("[%d] --------- {%s} no result \n", __LINE__, __FUNCTION__);
    }
    dlxDestroy(&obj);
}
