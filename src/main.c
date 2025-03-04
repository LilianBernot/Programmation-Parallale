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

    double sequential_result, vectorial_result, vectorial_general_result;
    double sequential_time, vectorial_time, vectorial_general_time;
    clock_t start, end;

    // ---------------------------- Sequential ----------------------------

    start = clock();
    sequential_result = dist(U, V, N);
    end = clock();
    sequential_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Sequential ---\n");
    printf("Result: %lf\n", sequential_result);
    printf("Execution time: %lf\n", sequential_time);

    // ---------------------------- Vectorial Aligned ----------------------------

    start = clock();
    vectorial_result = vect_dist(U, V, N);
    end = clock();
    vectorial_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Vectorial Aligned ---\n");
    printf("Result: %lf\n", vectorial_result);
    printf("Result difference: %lf\n", vectorial_result - sequential_result);
    printf("Execution time: %lf\n", vectorial_time);
    printf("Speed up: %lf\n", sequential_time / vectorial_time);

    // ---------------------------- Vectorial General ----------------------------

    start = clock();
    vectorial_general_result = vect_dist_gen(U, V, N);
    end = clock();
    vectorial_general_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Vectorial General ---\n");
    printf("Result: %lf\n", vectorial_general_result);
    printf("Result difference: %lf\n", vectorial_general_result - sequential_result);
    printf("Execution time: %lf\n", vectorial_general_time);
    printf("Speed up: %lf\n", sequential_time / vectorial_general_time);

    return 0;
}