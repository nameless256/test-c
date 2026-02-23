//
// Created by xiaoxianghui on 2025/4/9.
//

#include "oop.h"
#include "list_base.h"
#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#pragma region "list_node_base"

#undef className
#define className listNodeBase

oopClassDeclare()
oopClassDefine() {
    listNodeBase *prev, *next;
};

static inline oopFunc(void, show) {
    self->prev->next = self;
    self->next->prev = self;
}

static inline oopFunc(void, hide) {
    self->prev->next = self->next;
    self->next->prev = self->prev;
}

static inline oopFunc(void, insert, listNodeBase *other, bool after) {
    if (after) self->prev = other, self->next = other->next;
    else self->prev = other->prev, self->next = other;
    call(show);
}

static inline oopFunc(listNodeBase *, remove) {
    call(hide);
    self->next = self->prev = NULL;
    return self;
}

static inline oopFunc(void, init) {
    self->prev = self, self->next = self;
}

static inline oopCtor() {
    self->next = self->prev = NULL;
}

static inline oopDtor() {
    self->next = self->prev = NULL;
}

#pragma endregion

#pragma region "list_node"

#undef classBaseName
#undef className
#define classBaseName listNodeBase
#define className listNode

oopClassDeclare()
oopClassDefine() {
    oopInherit();
    uint8_t data[];
};

static inline oopCtor() {
    super(ctor);
}

static inline oopDtor() {
    super(dtor);
}

#pragma endregion

typedef struct listBase listBase;
struct listBase {
    listNodeBase impl;
    size_t TSize;
    size_t size;
};

static void listBase_ctor(listBase *self, size_t TSize) {
    listNodeBase_ctor(&self->impl);
    self->TSize = TSize;
    self->size = 0;
}

static int listBase_empty(listBase *self) {
    return self->size == 0;
}

static void listBase_push_front(listBase *self, void *data) {
    listNode *oopObjNewEx(listNode, node, self->TSize);
    listNodeBase_init(node->base);
    memcpy(node->data, data, self->TSize);
    listNodeBase_insert(node->base, &self->impl, true);
    self->size++;
}

static void listBase_push_back(listBase *self, void *data) {
    listNode *oopObjNewEx(listNode, node, self->TSize);
    listNodeBase_init(node->base);
    memcpy(node->data, data, self->TSize);
    listNodeBase_insert(node->base, &self->impl, false);
    self->size++;
}

static void listBase_pop_front(listBase *self) {
    listNode *node = (listNode *) listNodeBase_remove(self->impl.next);
    oopObjDelete(listNode, node);
}

static void listBase_pop_back(listBase *self) {
    listNode *node = (listNode *) listNodeBase_remove(self->impl.prev);
    oopObjDelete(listNode, node);
}
