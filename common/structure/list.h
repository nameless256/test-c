//
// Created by xiaoxianghui on 2023/4/20.
//

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct link2Node {
    struct link2Node *prev, *next;
};

typedef struct link2Node listNode;

#define listNodeInit(name) { &(name), &(name) }

#ifndef structOffsetOf
#define structOffsetOf(type, member) ((uintptr_t)(&((type *)0)->member))
#endif

#ifndef containerOf
#define containerOf(ptr, type, member) ((type *)((uintptr_t *)(ptr) - structOffsetOf(type, member)))
#endif

static inline void listNodeShow(listNode *node) {
    node->prev->next = node;
    node->next->prev = node;
}

static inline void listNodeHide(listNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static inline void listAdd(listNode *node, listNode *head) {
    node->prev = head, node->next = head->next;
    head->next->prev = node, head->next = node;
}

static inline listNode *listDel(listNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node;
    node->prev = node;
    return node;
}

static inline bool listIsEmpty(const listNode *head) {
    return head->next == head && head->prev == head;
}

#endif //LIST_H
