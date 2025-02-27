#include <stdio.h>
#include <math.h>

double dist(float *U, float *V, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += sqrt((U[i] * U[i] + V[i] * V[i]) / (1 + (U[i] * V[i]) * (U[i] * V[i])));
    }
    return sum;
}

// Exemple d'utilisation
// int main() {
//     float U[] = {1.0, 2.0, 3.0};
//     float V[] = {4.0, 5.0, 6.0};
//     int n = 3;

//     double result = dist(U, V, n);
//     printf("Distance: %lf\n", result);

//     return 0;
// }
