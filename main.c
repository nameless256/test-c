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

#define structName test1
#define structMember(f) \
mcrDispatch(f, a, int8_t a) \
mcrDispatch(f, b, char* b) \
mcrDispatch(f, c, int8_t c, 4)
#define structMataRemain
#include "def_struct.h"
#include "def_meta_struct.h"

#include "vector_base.h"

int main() {
    system("chcp 65001");
    clock_t start = clock();

    foreachMetaType(i) {
        printf("0xOil: [%d]{%s} %s \n", __LINE__, __FUNCTION__, i->base.name);
    }

    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    //    system("pause");
    return 0;
}

/** @} */
