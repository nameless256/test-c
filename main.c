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
#include <string.h>
//#include "oop_usage.h"
#include "tool.h"

/**
 * @defgroup Main
 * @{
 */

int main() {
    system("chcp 65001");
    clock_t start = clock();

//    oopUsage();
    size_t tempSize = 64;
    autoReleaseBuffer(char *, temp, tempSize) {
        printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
        memset(temp, 0, tempSize);
        strcpy(temp, "Hello, World!");
        printf("[%d] --------- {%s} %s \n", __LINE__, __FUNCTION__, temp);
        autoReleaseFile(test, "../test.txt", "w+") {
            printf("[%d] --------- {%s} \n", __LINE__, __FUNCTION__);
            fputs(temp, test);
        }
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    return 0;
}

/** @} */
