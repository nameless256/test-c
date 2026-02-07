//
// Created by xiaoxianghui on 2025/4/9.
//

#include <stdbool.h>
#include "list_base.h"

#include <stdint.h>

typedef struct listNode listNode;
struct listNode {
    listNode *prev, *next;
    uint8_t data[];
};

typedef struct alloc alloc;
struct alloc {
    void *(*alloc)(size_t);
    void (*free)(void *);
};

typedef struct list list;
struct list {
    alloc *alloc;
    listNode *head;
    listNode *tail;
    size_t size;
};

#ifndef structOffsetOf
#define structOffsetOf(type, member) ((uintptr_t)(&((type *)0)->member))
#endif

static inline void showNode(listNode *node) {
    node->prev->next = node;
    node->next->prev = node;
}

static inline void hideNode(listNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static inline void addNode(listNode *node, listNode *head) {
    node->prev = head, node->next = head->next;
    head->next->prev = node, head->next = node;
}

static inline listNode *deleteNode(listNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node;
    node->prev = node;
    return node;
}

static inline bool isEmpty(const listNode *head) {
    return head->next == head && head->prev == head;
}
