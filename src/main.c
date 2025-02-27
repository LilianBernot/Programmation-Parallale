#include "operations.h"
#include "utils.h"

#include <immintrin.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// #define N (1024 * 1024) // Large value for benchmarking
#define N (16 * 16)

int main() {
    float *U = (float *)aligned_alloc(32, N * sizeof(float));
    float *V = (float *)aligned_alloc(32, N * sizeof(float));

    initialize_random(U, N);
    initialize_random(V, N);

    double sequential_result;
    double sequential_time;
    clock_t start, end;

    start = clock();
    sequential_result = dist(U, V, N);
    end = clock();
    sequential_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential result: %lf\n", sequential_result);
    printf("Sequential execution time: %lf\n", sequential_time);

    return 0;
}