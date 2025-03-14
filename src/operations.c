#include <stdio.h>
#include <math.h>
#include <immintrin.h>  // AVX intrinsics
#include <pthread.h>

#define N_MULTIPLE 8 // N is a multiple of

double dist(float *U, float *V, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += sqrt((U[i] * U[i] + V[i] * V[i]) / (1 + (U[i] * V[i]) * (U[i] * V[i])));
    }
    return sum;
}

double vect_dist(float *U, float *V, int n) {
    __m256 sum_vec = _mm256_setzero_ps();  // Initialize vector sum

    for (int i = 0; i < n; i += N_MULTIPLE) {
        // Load N_MULTIPLE floats from U and V
        __m256 u = _mm256_load_ps(&U[i]);
        __m256 v = _mm256_load_ps(&V[i]);

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
    float *sum_array = (float *)aligned_alloc(32, N_MULTIPLE * sizeof(float));;
    _mm256_store_ps(sum_array, sum_vec);
    double sum;
    for (int i = 0; i < N_MULTIPLE; i++) {
        sum += sum_array[i];
    }

    return sum;
}

double vect_dist_gen(float *U, float *V, int n){
    __m256 sum_vec = _mm256_setzero_ps();  // Initialize vector sum

    for (int i = 0; i < n; i += N_MULTIPLE) {
        // DIFF : Use unaligned loads
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
    // DIFF : unaligned store
    _mm256_storeu_ps(sum_array, sum_vec);
    double sum;
    for (int i = 0; i < N_MULTIPLE; i++) {
        sum += sum_array[i];
    }

    return sum;
};

// ---------------------------- Multthread implementaion ----------------------------

pthread_mutex_t mutex;  // Declare a mutex
double multithread_sum = 0; // Shared variable

typedef struct {
    float *U;
    float *V;
    int start;
    int end;
} ThreadData;

void *thread_dist(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    // We add offset to the pointer
    float *U = data->U + data->start;
    float *V = data->V + data->start;

    // We wil read the vector until that point
    int end_vec = data->end - data->start;
    
    double partial_sum = dist(U, V, end_vec);

    // Protect shared resource
    pthread_mutex_lock(&mutex);
    multithread_sum += partial_sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *thread_dist_vect(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    // We add offset to the pointer
    float *U = data->U + data->start;
    float *V = data->V + data->start;

    // We wil read the vector until that point
    int end_vec = data->end - data->start;
    
    double partial_sum = vect_dist(U, V, end_vec);

    // Protect shared resource
    pthread_mutex_lock(&mutex);
    multithread_sum += partial_sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void distPar(float *U, float *V, int n, int nb_threads, int mode){
    pthread_t threads[nb_threads];
    ThreadData data[nb_threads];
    int chunk_size = n / nb_threads;

    multithread_sum = 0.0; // Reset shared sum
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    for (int i = 0; i< nb_threads; i++){
        data[i].U = U;
        data[i].V = V;
        data[i].start = i*chunk_size;
        data[i].end = (i == nb_threads - 1) ? n : (i+1)*chunk_size;
    }

    if (mode==0){
        for (int i = 0; i< nb_threads; i++){
            pthread_create(&threads[i], NULL, thread_dist, &data[i]);
        } 
    } else if (mode==1)
    {
        for (int i = 0; i< nb_threads; i++){
            pthread_create(&threads[i], NULL, thread_dist_vect, &data[i]);
        } 
    }
    

    for (int i = 0; i< nb_threads; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy mutex
}
