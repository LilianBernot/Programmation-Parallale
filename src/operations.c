#include <stdio.h>
#include <math.h>
#include <immintrin.h>  // AVX intrinsics

double dist(float *U, float *V, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += sqrt((U[i] * U[i] + V[i] * V[i]) / (1 + (U[i] * V[i]) * (U[i] * V[i])));
    }
    return sum;
}

double vect_dist(float *U, float *V, int n) {
    __m256 sum_vec = _mm256_setzero_ps();  // Initialize vector sum

    for (int i = 0; i < n; i += 8) {
        // Load 8 floats from U and V
        __m256 u = _mm256_loadu_ps(&U[i]);
        __m256 v = _mm256_loadu_ps(&V[i]);

        // Compute U[i] * U[i] and V[i] * V[i]
        __m256 u2 = _mm256_mul_ps(u, u);
        __m256 v2 = _mm256_mul_ps(v, v);

        // Compute (U[i] * V[i])
        __m256 uv = _mm256_mul_ps(u, v);
        __m256 uv2 = _mm256_mul_ps(uv, uv); // (U[i] * V[i])^2

        // Compute numerator: sqrt((U[i]^2 + V[i]^2) / (1 + (U[i] * V[i])^2))
        __m256 num = _mm256_add_ps(u2, v2);  // U[i]^2 + V[i]^2
        __m256 den = _mm256_add_ps(_mm256_set1_ps(1.0f), uv2);  // 1 + (U[i] * V[i])^2
        __m256 div = _mm256_div_ps(num, den);  // (U[i]^2 + V[i]^2) / (1 + (U[i] * V[i])^2)

        __m256 result = _mm256_sqrt_ps(div);  // sqrt operation

        // Accumulate into sum_vec
        sum_vec = _mm256_add_ps(sum_vec, result);
    }

    // Horizontal sum of sum_vec
    float sum_array[8];
    _mm256_storeu_ps(sum_array, sum_vec);
    double sum;
    for (int i = 0; i < 8; i++) {
        sum += sum_array[i];
    }

    return sum;
}