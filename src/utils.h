#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> // for size_t

extern const size_t ALIGNMENT;

void initialize_random(float *arr, int n);

void print_vector(float *arr, int n);

#endif
