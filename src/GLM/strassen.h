#ifndef STRASSEN_H_
#define STRASSEN_H_

#include <omp.h>
#include <cmath>
#include <Rcpp.h>

#define cores omp_get_max_threads()

void strassenR(double *X, double *Y, double *Z, int n, int p, int m);

void strassen(double *X, double *Y, double *Z, int n, int p, int m);

void ijkalgorithm(double *X, double *Y, double *Z, int n, int p, int m);

void add(double *X, double *Y, double *Z, int n, int m);

void substract(double *X, double *Y, double *Z, int n, int m);

#endif
