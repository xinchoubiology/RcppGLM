#include <omp.h>
#include <Rcpp.h>

#ifndef DGEMM_H_
#define DEGMM_H_

using namespace Rcpp;

#ifndef DEFAULTBLOCK
#define DEFAULTBLOCK 500
#endif

#ifndef BOFFSET
#define BOFFSET 12
#endif

#define cores omp_get_max_threads()
#define x(i, j) xb[(i) * (block + BOFFSET) + (j)]
#define y(i, j) yb[(i) * (block + BOFFSET) + (j)]
#define z(i, j) zb[(i) * (block + BOFFSET) + (j)]
#define MIN(a, b) ((a) < (b) ? (a) : (b))


void matrixinit(double *Z, int n, int m);

void dgemm(double * X, double * Y, double * Z, int n, int p, int m);

void dgemm_block(double * X, double * Y, double * Z, int n, int p, int m);


#endif
