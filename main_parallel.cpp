//#include <limits.h>
//#include <stdint.h>
//#include <asm-generic/errno.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>
#include <cuda_runtime.h>
//#include <stdbool.h>

const int DEFAULT_ARRAY_SIZE = 1000000;
const int DEFAULT_RUNS = 100;
const int DEFAULT_THREADS = 256;
const int DEFAULT_BLOCKS = 1;

float* CreateArray(const int SIZE) {
    float* int_array = (float*) malloc(sizeof(float) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        int_array[i] = rand()%100;
    }
    return int_array;
}

void PrintArray(const int* array, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

int GetEnvArraySize() {
    char* array_size_char = getenv("ARRAY_SIZE");
    int array_size_int = DEFAULT_ARRAY_SIZE;
    if (array_size_char != NULL) {
        array_size_int = atoi(array_size_char);
    } else {
        printf(
            "Переменная среды ARRAY_SIZE не получена, "
            "используем значение по умолчанию: %d \n", DEFAULT_ARRAY_SIZE
        );
    }
    return array_size_int;
}

int GetEnvThreads() {
    char* thread_char = getenv("THREADS");
    int thread_int = DEFAULT_THREADS;
    if (thread_char != NULL) {
        thread_int = atoi(thread_char);
    } else {
        printf(
            "Переменная среды THREADS не получена, "
            "используем значение по умолчанию: %d \n", DEFAULT_THREADS
        );
    }
    return thread_int;
}

int GetEnvBlocks() {
    char* block_char = getenv("BLOCKS");
    int block_int = DEFAULT_BLOCKS;
    if (block_char != NULL) {
        block_int = atoi(block_char);
    } else {
        printf(
            "Переменная среды BLOCKS не получена, "
            "используем значение по умолчанию: %d \n", DEFAULT_BLOCKS
        );
    }
    return block_int;
}

int GetEnvRuns() {
    char* runs_char = getenv("RUNS");
    int runs_int = DEFAULT_RUNS;
    if (runs_char != NULL) {
        runs_int = atoi(runs_char);
    } else {
        printf(
            "Переменная среды RUNS не получена, "
            "используем значение по умолчанию: %d \n", DEFAULT_RUNS
        );
    }
    return runs_int;
}

float SumElementsOfArray(const float* array, const int SIZE) {
    float result = 0;
    for (int i = 0; i < SIZE; i++) {
        result += array[0];
    }
    return result;
}

int main(int argc, char** argv) {
    srand(time(0));
    //srand(1);
    const int ARRAY_SIZE = GetEnvArraySize();
    const int RUNS = GetEnvRuns();
    const int THREADS = GetEnvThreads();
    const int BLOCKS = GetEnvBlocks();

    printf("Размер массива: %d\n", ARRAY_SIZE);
    printf("Выполнений: %d\n", RUNS);
    printf("Потоков в блоке: %d\n", THREADS);
    printf("Блоков: %d\n", BLOCKS);
    
    // Таймер
    struct timespec begin, end;
    double exec_time = 0.0;

    // Цикл выполнения задачи и подсчёта времени её выполнения
    for (int i = 0; i < RUNS; i++) {

        float* float_array = NULL;
        float_array = CreateArray(ARRAY_SIZE);

        clock_gettime(CLOCK_REALTIME, &begin); // Начало таймера

        SumElementsOfArray(float_array, ARRAY_SIZE);

        clock_gettime(CLOCK_REALTIME, &end); // Конец таймера
        exec_time += (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9;

        free(float_array);
    }

    double mean_exec_time = exec_time / RUNS;
    printf("Общее время выполнения: %f сек. \n", exec_time);
    printf("Среднее время выполнения: %f сек.", mean_exec_time);

    return 0;
}
