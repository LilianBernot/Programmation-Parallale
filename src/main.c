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

    double result = dist(U, V, N);

    printf("Distance: %lf\n", result);

    return 0;
}