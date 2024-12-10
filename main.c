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
#include <pthread.h>

/**
 * @defgroup Main
 * @{
 */

// 线程函数
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is running\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    system("chcp 65001");
    clock_t start = clock();

    pthread_t threads[5];
    int thread_ids[5];
    int result;

    // 创建5个线程
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i;
        result = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
        if (result != 0) {
            printf("Error creating thread %d\n", i);
            exit(-1);
        }
    }

    // 等待所有线程完成
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution\n");

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.5f \n", elapsed);
    return 0;
}

/** @} */
