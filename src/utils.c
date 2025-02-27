#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h" 
#include "operations.h"

// Recommandé par AVX
const size_t ALIGNMENT = 32;  

// Fonction pour générer un tableau de nombres flottants aléatoires entre -10 et 10
void initialize_random(float *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = ((float)rand() / RAND_MAX) * 20.0 - 10.0;
    }
}

// Fonction pour afficher un vecteur
void print_vector(float *arr, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("]\n");
}


// int main() {
//     srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

//     // int sizes[] = {4, 8, 80}; // Tailles des vecteurs à tester
//     int sizes[] = {8};
//     int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

//     for (int j = 0; j < num_sizes; j++) {
//         int n = sizes[j];

//         float *U = (float *)malloc(n * sizeof(float));
//         float *V = (float *)aligned_alloc(ALIGNMENT, n * sizeof(float));

//         if (U == NULL || V == NULL) {
//             printf("Erreur d'allocation mémoire\n");
//             return 1;
//         }

//         fill_random_vector(U, n);
//         fill_random_vector(V, n);

//         printf("\n=== Vecteurs de taille %d ===\n", n);

//         printf("U = ");
//         print_vector(U, n);

//         printf("\nV (aligné) = ");
//         print_vector(V, n);

//         free(U);
//         free(V);
//     }

//     return 0;
// }