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

int main() {
    system("chcp 65001");
    clock_t start = clock();

    test();

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    //    system("pause");
    return 0;
}

/** @} */
