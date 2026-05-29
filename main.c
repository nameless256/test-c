/**
 *****************************************************************************************
 * Copyright(c) 20XX, XXX Corporation. All rights reserved.
 *****************************************************************************************
 * @file    main.c
 * @brief
 * @author
 * @date
 * @version 0.0.1
 *****************************************************************************************
 * @attention
 * <h2><center>&copy; COPYRIGHT 20XX XXX Corporation</center></h2>
 *****************************************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vector.h"

/**
 * @defgroup Main
 * @{
 */

void test() {
    vector(double, map, 10, 3.14);
    for (int i = 0; i < 10; ++i) {
        printf("%.2f ", vector_at(map, i));
    }
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        vector_at(map, i) = 1.25;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%.2f ", vector_at(map, i));
    }
    printf("\n");
}

typedef struct string string;

struct string
{
    objBase base;
    size_t size;
    size_t length;
    uint8_t *data;
};

bool string_ctor(objBase *obj) {
    return false;
}

void string_dtor(objBase *obj) {
    string *self = (string*)obj;
    if (self->data) {
        free(self->data);
        self->data = NULL;
    }
    self->length = 0;
    self->size = 0;
}

bool string_copy(objBase *obj, objBase *other) {
    string *self = (string*)obj;
    string *src = (string*)other;
    if (alloc_safe((void**)&self->data, src->size, 0)) return true;
    memcpy(self->data, src->data, src->size);
    self->length = src->length;
    self->size = src->size;
    return false;
}

classMeta string_meta = {
    .base = {
        .name = "string",
        .size = sizeof(string),
        .quals = qual_Null,
        .id = typeId_Class,
    },
    .ctor = string_ctor,
    .dtor = string_dtor,
    .copy = string_copy,
};

static void obj_dtor_base(classMeta *class, objBase *obj);

static void obj_dtor_member_base(classMeta *class, objBase *obj, size_t cnt) {
    for (size_t i = cnt; i > 0; i--) {
        const fieldMeta *field = class->fields[i - 1];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        obj_dtor_base((classMeta*)&type->classMeta, (objBase*)((char*)obj + field->base.ofs));
    }
}

static void obj_dtor_base(classMeta *class, objBase *obj) {
    obj_dtor_member_base(class, obj, class->cnt);
    if (class->dtor) class->dtor(obj);
    if (class->baseClass) obj_dtor_base(class->baseClass, obj);
}

void obj_dtor(objBase *obj) {
    obj_dtor_base(obj->class, obj);
}

static bool obj_ctor_base(classMeta *class, objBase *obj) {
    if (class->baseClass) {
        if (obj_ctor_base(class->baseClass, obj)) return true;
    }
    for (size_t i = 0; i < class->cnt; i++) {
        const fieldMeta *field = class->fields[i];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        if (obj_ctor_base((classMeta*)&type->classMeta, (objBase*)((char*)obj + field->base.ofs))) {
            obj_dtor_member_base(class, obj, i);
            return true;
        }
    }
    if (class->ctor) {
        if (class->ctor(obj)) {
            return true;
        }
    }
    return false;
}

bool obj_ctor(objBase *obj) {
    return obj_ctor_base(obj->class, obj);
}

static bool obj_copy_base(classMeta *class, objBase *obj, objBase *other) {
    for (size_t i = 0; i < class->cnt; i++) {
        const fieldMeta *field = class->fields[i];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        if (obj_copy_base((classMeta*)&type->classMeta, (objBase*)((char*)obj + field->base.ofs),
                          (objBase*)((char*)other + field->base.ofs))) {
            for (size_t j = i; j > 0; j--) {
                const fieldMeta *prev_field = class->fields[j - 1];
                if (prev_field->base.isBitField) continue;
                const typeMeta *prev_type = prev_field->base.base.type;
                if (prev_type->base.id != typeId_Class) continue;
                obj_dtor_base((classMeta*)&prev_type->classMeta, (objBase*)((char*)obj + prev_field->base.ofs));
            }
            return true;
        }
    }
    if (class->copy) return class->copy(obj, other);
    return false;
}

bool obj_copy(objBase *obj, objBase *other) {
    return obj_copy_base(obj->class, obj, other);
}

int main() {
    system("chcp 65001");
    clock_t start = clock();

    // test();

    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    //    system("pause");
    return 0;
}

/** @} */
