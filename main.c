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

#include "meta.h"

/**
 * @defgroup Main
 * @{
*/

#include "vector_base.h"
#include "obj.h"

int main() {
    system("chcp 65001");
    clock_t start = clock();

    vector_base var CLEANUP(obj_dtor) = {(void *) &vector_base_meta};
    obj_ctor(&var);

    vector_base *var2 = malloc(sizeof(vector_base));
    if (var2) obj_ctor(var2);

    if (var2) {
        obj_dtor(var2);
        free(var2);
        var2 = NULL;
    }

    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    //    system("pause");
    return 0;
}

/** @} */
