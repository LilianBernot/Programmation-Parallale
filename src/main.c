#include "operations.h"
#include "utils.h"

#include <immintrin.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N (1024 * 1024) // Large value for benchmarking
// #define N (16 * 16)
#define NB_THREADS 8 // Number of threads for parallel execution

int main() {
    float *U = (float *)aligned_alloc(32, N * sizeof(float));
    float *V = (float *)aligned_alloc(32, N * sizeof(float));

    initialize_random(U, N);
    initialize_random(V, N);

    double sequential_result, vectorial_result, vectorial_general_result, multithread_scalar_result, multithread_vectorial_result;
    double sequential_time, vectorial_time, vectorial_general_time, multithread_scalar_time, multithread_vectorial_time;
    clock_t start, end;

    // ---------------------------- Print parameters ----------------------------
    printf("--- Parameters ---\n");
    printf("N: %d\n", N);
    printf("NB_THREADS: %d\n\n", NB_THREADS);

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

    // ---------------------------- Multithread Scalar ----------------------------

    start = clock();
    multithread_scalar_result = distPar(U, V, N, NB_THREADS, 0);
    end = clock();
    multithread_scalar_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Multithread Scalar ---\n");
    printf("Result: %lf\n", multithread_scalar_result);
    printf("Result difference: %lf\n", multithread_scalar_result - sequential_result);
    printf("Execution time: %lf\n", multithread_scalar_time);
    printf("Speed up: %lf\n", sequential_time / multithread_scalar_time);
    
    // ---------------------------- Multithread Vectorial ----------------------------

    start = clock();
    multithread_vectorial_result = distPar(U, V, N, NB_THREADS, 1);
    end = clock();
    multithread_vectorial_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Multithread Vectorial ---\n");
    printf("Result: %lf\n", multithread_vectorial_result);
    printf("Result difference: %lf\n", multithread_vectorial_result - sequential_result);
    printf("Execution time: %lf\n", multithread_vectorial_time);
    printf("Speed up: %lf\n", sequential_time / multithread_vectorial_time);
        
    return 0;
}