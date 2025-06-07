#include <limits.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

const int DEFAULT_ARRAY_SIZE = 1000000;
const int DEFAULT_RUNS = 100;
const int DEFAULT_HW_THREADS = 1;

int* CreateArray(const int SIZE) {
    int* int_array = (int*) malloc(sizeof(int) * SIZE);
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

int GetEnvHwThreads() {
    char* hw_thread_char = getenv("HW_THREADS");
    int hw_thread_int = DEFAULT_HW_THREADS;
    if (hw_thread_char != NULL) {
        hw_thread_int = atoi(hw_thread_char);
    } else {
        printf(
            "Переменная среды HW_THREADS не получена, "
            "используем значение по умолчанию: %d \n", DEFAULT_HW_THREADS
        );
    }
    return hw_thread_int;
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

int main(int argc, char** argv) {
    srand(time(0));
    //srand(1);
    const int ARRAY_SIZE = GetEnvArraySize();
    const int RUNS = GetEnvRuns();
    const int HW_THREADS = GetEnvHwThreads();
    bool parallel_mode = false; 

    if (HW_THREADS > 1) {
        parallel_mode = true;
        printf("Программа отработает в параллельном "
                "режиме (используемых аппаратных потоков > 1)\n"
        );
    } else {
        printf("Программа отработает в последовательном "
                "режиме (используемых аппаратных потоков = 1)\n"
        );
    }
    
    // Таймер
    struct timespec begin, end;
    double exec_time = 0.0;

    // Цикл выполнения задачи и подсчёта времени её выполнения
    for (int i = 0; i < RUNS; i++) {

        int* int_array = NULL;
        int_array = CreateArray(ARRAY_SIZE);

        clock_gettime(CLOCK_REALTIME, &begin); // Начало таймера

        clock_gettime(CLOCK_REALTIME, &end); // Конец таймера
        exec_time += (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9;

        free(int_array);
    }

    double mean_exec_time = exec_time / RUNS;
    printf("Общее время выполнения: %f сек. \n", exec_time);
    printf("Среднее время выполнения: %f сек.", mean_exec_time);

    return 0;
}
