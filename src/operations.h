#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <math.h>

extern double multithread_sum;

double dist(float *U, float *V, int n);

double vect_dist(float *U, float *V, int n);

double vect_dist_gen(float *U, float *V, int n);

float distPar(float *U, float *V, int n, int nb_threads, int mode);

#endif
