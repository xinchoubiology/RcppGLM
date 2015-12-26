#include "dgemm.h"

void matrixinit(double *Z, int n, int m)
{
    #pragma omp parallel for num_threads(cores)
    for(int i = 0; i < m * n; i++){
      Z[i] = 0;
    }
}

void dgemm(double * X, double * Y, double * Z, int n, int p, int m)
{
    Rprintf("DGEMM without blocked\n");
    // t(Z) = t(Y) %*% t(X)
    int i, j, k;
    #pragma omp parallel num_threads(cores) private(i, j, k) shared(X, Y)
    {
      #pragma omp for
      for(int j = 0; j < m; j++){
        for(int k = 0; k < p; k++){
          for(int i = 0; i < n; i++){
            Z[j * n + i] += Y[j * p + k] * X[k * n + i];
          }
        }
      }
    }
}

void dgemm_block(double * X, double * Y, double * Z, int n, int p, int m)
{
    int i, j, k, ii, jj, kk, ig, jg, kg;    /* dummies */
    int block;      /* tile size of matroces */
    int num_error;  /* flag that signals that requestd and obtained numbers of threads */

    block = DEFAULTBLOCK;

    #pragma omp parallel num_threads(1) private(i, j, k, ii, jj, kk, ig, jg, kg)
    {
      double *xb, *yb, *zb;  /* matrix blocks for local temporary copies (b := block)*/
      if(block > 0){
        xb = (double *)malloc(block * (block + BOFFSET) * sizeof(double) * 3);
        if(!xb){
          num_error = 1;
          Rprintf("Could not allocate space for matrix tiles on thread %d\n");
        }
        yb = xb + block * (block + BOFFSET);
        zb = yb + block * (block + BOFFSET);
        #pragma omp for
        for(jj = 0; jj < m; jj+=block){
          for(kk = 0; kk < p; kk+=block){

            for(jg=jj,j=0; jg < MIN(jj+block, m); jg++,j++){
              for(kg=kk,k=0; kg < MIN(kk+block, p); kg++,k++){
                y(j, k) = Y[jg * p + kg];
              }
            }

            for(ii = 0; ii < n; ii+=block){

              for(kg=kk,k=0; kg < MIN(kk+block, p); kg++,k++){
                for(ig=ii,i=0; ig < MIN(ii+block, n); ig++,i++){
                  x(i, k) = X[kg * n + ig];
                }
              }

              for(jg=jj,j=0; jg < MIN(jj+block, m); jg++,j++){
                for(ig=ii,i=0; ig < MIN(ii+block, n); ig++,i++){
                  z(j, i) = 0.0;
                }
              }

              for(jg=jj,j=0; jg < MIN(jj+block, m); jg++,j++){
                for(ig=ii,i=0; ig < MIN(ii+block, n); ig++,i++){
                  for(kg=kk,k=0; kg < MIN(kk+block, p); kg++,k++){
                    z(j, i) += y(j, k) * x(i, k);
                  }
                }
              }

              for(jg=jj,j=0; jg < MIN(jj+block, m); jg++,j++){
                for(ig=ii,i=0; ig < MIN(ii+block, n); ig++,i++){
                  Z[jg * n + ig] += z(j, i);
                }
              }
            }
          }
        }
      }
    }
}



