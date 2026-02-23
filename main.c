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
#include "type_meta.h"

/**
 * @defgroup Main
 * @{
 */

int main() {
    system("chcp 65001");
    clock_t start = clock();

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
#define foreach(valName, container) for (int i = 0, valName = container[i]; i < ARRAY_SIZE(container); ++i)
    foreach(bbb, arr) {
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
//    system("pause");
    return 0;
}

/** @} */
