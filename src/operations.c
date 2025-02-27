#include <stdio.h>
#include <math.h>

double dist(float *U, float *V, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += sqrt((U[i] * U[i] + V[i] * V[i]) / (1 + (U[i] * V[i]) * (U[i] * V[i])));
    }
    return sum;
}
