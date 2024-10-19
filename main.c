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
#include <stdio.h>
#include <time.h>
#include "oop_usage.h"

/**
 * @defgroup Main
 * @{
 */

int main() {
    clock_t start = clock();

    oopUsage();

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    return 0;
}

/** @} */
