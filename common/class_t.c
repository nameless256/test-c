//
// Created by HASEE on 2024/9/22.
//

#include "class_t.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void ctor(struct class_t *cThis) {
    if (cThis) memset(cThis, 0, sizeof(struct class_t));
}

static void ctorCopy(struct class_t *cThis, struct class_t *src) {
    if (cThis && src) memcpy(cThis, src, sizeof(struct class_t));
}

static void dtor(struct class_t *cThis) {
}

struct class_t objClass = {
    .base = NULL,
    .ctor = ctor,
    .ctorCopy = ctorCopy,
    .dtor = dtor,
    .attribute = 0,
    .private = NULL,
};

class_t obj_create(void) {
    class_t obj = malloc(sizeof(struct class_t));
    if (obj == NULL) return NULL;
    objClass.ctor(obj);
    return obj;
}

void obj_destroy(class_t *obj) {
    if (*obj == NULL) return;
    objClass.dtor(*obj);
    free(*obj);
    *obj = NULL;
}
