//
// Created by xiaoxianghui on 2024/1/31.
//

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "dlx.h"

struct dlxCol;

typedef struct dlxNode {
    struct dlxNode *up, *down;
    struct dlxNode *left, *right;
    struct dlxCol *col;
    uint16_t rowId;
} dlxNode, *dlxCursor;

typedef struct dlxCol {
    struct dlxNode node;
    uint16_t id, size;
} dlxCol;

/// 指针操作宏定义
#define dlxNodeVHide(node) (node)->up->down = (node)->down, (node)->down->up = (node)->up
#define dlxNodeHHide(node) (node)->left->right = (node)->right, (node)->right->left = (node)->left
#define dlxNodeVShow(node) (node)->up->down = (node), (node)->down->up = (node)
#define dlxNodeHShow(node) (node)->left->right = (node), (node)->right->left = (node)
#define dlxNodeVIsEmpty(node) ((node)->up == (node) && (node)->down == (node))
#define dlxNodeHIsEmpty(node) ((node)->left == (node) && (node)->right == (node))
#define dlxNodeInit(node) (node)->up = (node)->down = (node)->left = (node)->right = (node)

oopClassDefine() {
    dlxCol *col; ///< 列首节点数组
    dlxCursor *first; ///< 行首节点指针数组
    uint16_t *stack; ///< 解答栈
    uint16_t *result; ///< 存放搜索到的最后一个解
    uint16_t resultLen;
    uint16_t colCount; ///< 创建时确认的 列的个数
    uint16_t rowCount; ///< 创建时确认的 行的个数
};

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

oopPrivate(void, hideColById, uint16_t colId) {
    dlxCol *col = &self->col[colId];
    dlxCursor r, c;
    dlxNodeHHide(&col->node);
    for (r = col->node.down; r != &col->node; r = r->down)
        for (c = r->right; c != r; c = c->right) dlxNodeVHide(c), --(c->col->size);
}

oopPrivate(void, showColById, uint16_t colId) {
    dlxCol *col = &self->col[colId];
    dlxCursor r, c;
    for (r = col->node.down; r != &col->node; r = r->down)
        for (c = r->right; c != r; c = c->right) dlxNodeVShow(c), ++(c->col->size);
    dlxNodeHShow(&col->node);
}

oopPrivate(dlxCol *, getMinCol) {
    dlxNode *minCol = self->col[0].node.right;
    for (dlxCursor i = minCol; i != &self->col[0].node; i = i->right)
        if (i->col->size < minCol->col->size) minCol = i;
    return minCol->col;
}

oopPrivate(bool, isEmpty) {
    return dlxNodeHIsEmpty(&self->col[0].node);
}

oopPrivate(uint16_t, dance, uint16_t idx, uint16_t count) {
    uint16_t resultCount = 0; // 0: 无解
    if (dlx_isEmpty(self)) { // 有解
        if (self->result != NULL) {
            memset(self->result, 0, self->resultLen * sizeof(uint16_t));
            memcpy(self->result, self->stack, self->resultLen * sizeof(uint16_t));
        }
        return 1;
    } else if (idx >= self->resultLen) {
        printf("[%d] --------- {%s} not enough results cached ! \n", __LINE__, __FUNCTION__);
        return 0;
    }
    dlxCol *minCol = dlx_getMinCol(self);
    dlx_hideColById(self, minCol->id);
    dlxCursor r, c;
    for (r = minCol->node.down; r != &minCol->node; r = r->down) {
        for (c = r->right; c != r; c = c->right) dlx_hideColById(self, c->col->id);
        self->stack[idx] = r->rowId; // 按递归调用顺序依次记录解的行号
        resultCount += dlx_dance(self, idx + 1, count);
        for (c = r->left; c != r; c = c->left) dlx_showColById(self, c->col->id);
        if (count == resultCount) break; // 需要的解都已找到
    }
    dlx_showColById(self, minCol->id);
    return resultCount; // 无解返回0并在下一分支搜索解
}

oopCreate(uint16_t rowCount, uint16_t colCount, uint16_t *result, uint16_t resultLen) {
    dlx *self = malloc(sizeof(dlx)); // 基本结构 空间分配
    self->colCount = colCount + 1; // + 1: 行首
    self->rowCount = rowCount + 1; // + 1: 列首
    self->result = result, self->resultLen = resultLen;
    self->stack = calloc(self->resultLen, sizeof(uint16_t));
    self->col = malloc(self->colCount * sizeof(dlxCol));
    // 列首节点数组 初始化
    for (uint16_t i = 0; i < self->colCount; ++i) {
        dlxNodeInit(&self->col[i].node);
        self->col[i].node.rowId = 0, self->col[i].node.col = &self->col[i];
        self->col[i].size = 0, self->col[i].id = i; // 标记第几列
    }
    // 按 列首节点数组顺序 依次链接 生成 列首链表
    for (uint16_t i = 0; i < colCount; ++i)
        dlxNodeHInsert(&self->col[(i + 1) % self->colCount].node, &self->col[i].node);
    self->first = (dlxCursor *) calloc(self->rowCount, sizeof(dlxCursor)); // + 1: 列首; 指针初始化 为 0
    self->first[0] = &self->col[0].node; // first[0] 指向首行 即 列首
    return self;
}

oopDestroy() {
    if (self == NULL) return;
    for (uint16_t i = 0; i < self->colCount; ++i) // 销毁 列首 的 垂直链表
        while (!dlxNodeVIsEmpty(&self->col[i].node)) free(dlxNodeRemove(self->col[i].node.down));
    free(self->stack), free(self->first), free(self->col), free(self);
}

oopPublic(bool, nodeAdd, uint16_t rowId, uint16_t colId) {
    // 确保不会有重复节点
    for (dlxCursor i = self->col[colId].node.down; i != &self->col[colId].node; i = i->down)
        if (i->rowId == rowId) return true;
    // 节点创建
    dlxNode *node = malloc(sizeof(dlxNode));
    node->rowId = rowId, node->col = &self->col[colId], node->col->size++;
    dlxNodeVInsert(node, &self->col[colId].node);
    if (self->first[rowId]) dlxNodeHInsert(node, self->first[rowId]);
    else self->first[rowId] = node->left = node->right = node; // 如果当前行为空则直接插入
    return false;
}

oopPublic(uint16_t, search, uint16_t count) {
    return dlx_dance(self, 0, count);
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
    dlx *obj = dlx_create(ROW_COUNT, COL_COUNT, result, ROW_COUNT);
    for (int y = 0; y < ROW_COUNT; ++y)
        for (int x = 0; x < COL_COUNT; ++x) if (matrix[y][x]) dlx_nodeAdd(obj, y + 1, x + 1);
    if (dlx_search(obj, 2)) {
        for (int i = 0; result[i]; ++i)
            printf("[%d] --------- {%s} %d \n", __LINE__, __FUNCTION__, result[i]);
    } else {
        printf("[%d] --------- {%s} no result \n", __LINE__, __FUNCTION__);
    }
    dlx_destroy(obj);
}
