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
        arr[i] = (rand() + 1) / (float)(RAND_MAX);
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