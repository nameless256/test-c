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

struct string {
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

static const fieldMeta string_fields[] = {
    {
        .base = {
            .dsc = {
                .ptr = (typeMeta*)&size_t_meta
            },
            .name = "size"
        },
        .ofs = structOfsOf(string, size)
    },
    {
        .base = {
            .dsc = {
                .ptr = (typeMeta*)&size_t_meta
            },
            .name = "length"
        },
        .ofs = structOfsOf(string, length)
    },
    {
        .base = {
            .dsc = {
                .str = "uint8_t *data",
            },
            .name = "data"
        },
        .ofs = structOfsOf(string, data)
    },
};

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
    .cnt = 3,
    .fields = string_fields,
};

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
