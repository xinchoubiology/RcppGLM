#include "strassen.h"


void ijkalgorithm(double *X, double *Y, double *Z, int n, int p, int m)
{
  int i, j, k;
  #pragma omp parallel num_threads(cores) private(i, j, k) shared(X, Y)
  {  
    #pragma omp for
    for(j = 0; j < m; j++){
      for(k = 0; k < p; k++){
        for(i = 0; i < n; i++){
          Z[j * n + i] += Y[j * p + k] * X[k * n + i];
        }
      }
    }
  }
}

void add(double *X, double *Y, double *Z, int n, int m){
    #pragma omp parallel for num_threads(cores)
    for(int j = 0; j < m; j++){
      for(int i = 0; i < n; i++){
        Z[j * n + i] = X[j * n + i] + Y[j * n + i];
      }
    }
}

void subtract(double *X, double *Y, double *Z, int n, int m){
    #pragma omp parallel for num_threads(cores)
    for(int j = 0; j < m; j++){
      for(int i = 0; i < n; i++){
        Z[j * n + i] = X[j * n + i] - Y[j * n + i];
      }
    }
}

void strassenR(double *X, double *Y, double *Z, int n, int p, int m, int thresh)
{
    if(n < thresh || p < thresh || m < thresh){
      ijkalgorithm(X, Y, Z, n, p, m);
      return;
    }
    else{
      const int nn = n / 2;
      const int pp = p / 2;
      const int mm = m / 2;
      double *a11 = new double[nn * pp](); double *a12 = new double[nn * pp]();
      double *a21 = new double[nn * pp](); double *a22 = new double[nn * pp]();
      double *b11 = new double[pp * mm](); double *b12 = new double[pp * mm]();
      double *b21 = new double[pp * mm](); double *b22 = new double[pp * mm]();
      double *p1 = new double[nn * mm](); double *p2 = new double[nn * mm]();
      double *p3 = new double[nn * mm](); double *p4 = new double[nn * mm]();
      double *p5 = new double[nn * mm](); double *p6 = new double[nn * mm]();
      double *p7 = new double[nn * mm](); 
      double *c11 = new double[nn * mm](); double *c12 = new double[nn * mm]();
      double *c21 = new double[nn * mm](); double *c22 = new double[nn * mm]();
      double *ar = new double[nn * pp](); double *br = new double[pp * mm]();
      double *cr = new double[nn * mm](); double *pr = new double[nn * mm]();
      
      #pragma omp parallel for num_threads(cores)
      for(int j = 0; j < mm; j++){
        for(int k = 0; k < pp; k++){
          b11[j * pp + k] = Y[j * p + k];
          b12[j * pp + k] = Y[j * p + (k + pp)];
          b21[j * pp + k] = Y[(j + mm) * p + k];
          b22[j * pp + k] = Y[(j + mm) * p + (k + pp)];
        }
      }
      
      #pragma omp parallel for num_threads(cores)
      for(int k = 0; k < pp; k++){
        for(int i = 0; i < nn; i++){
          a11[k * nn + i] = X[k * n + i];
          a12[k * nn + i] = X[k * n + (i + nn)];
          a21[k * nn + i] = X[(k + pp) * n + i];
          a22[k * nn + i] = X[(k + pp) * n + (i + nn)];
        }
      }
      
      // br = b11 + b22
      add(b11, b22, br, pp, mm);
      // ar = a11 + a22
      add(a11, a22, ar, nn, pp);
      // p1 = br %*% ar 
      strassenR(ar, br, p1, nn, pp, mm, thresh); 
      // p2 = (b21 + b22)a11
      add(b21, b22, br, pp, mm);
      strassenR(a11, br, p2, nn, pp, mm, thresh);
      // p3 = b11 %*% (a12 - a22)
      subtract(a12, a22, ar, nn, pp);
      strassenR(ar, b11, p3, nn, pp, mm, thresh);
      // p4 = b22 %*% (a21 - a11)
      subtract(a21, a11, ar, nn, pp);
      strassenR(ar, b22, p4, nn, pp, mm, thresh);
      // p5 = (b11 + b12)a22
      add(b11, b12, br, pp, mm);
      strassenR(a22, br, p5, nn, pp, mm, thresh);
      // p6 = (b21 - b11)(a11 + a12)
      subtract(b21, b11, br, pp, mm);
      add(a11, a12, ar, nn, pp);
      strassenR(ar, br, p6, nn, pp, mm, thresh);
      // p7 = (b12 - b22)(a21 + a22)
      subtract(b12, b22, br, pp, mm);
      add(a21, a22, ar, nn, pp);
      strassenR(ar, br, p7, nn, pp, mm, thresh);
      // c11 = p1 + p4 - p5 + p7
      add(p1, p4, cr, nn, mm);
      subtract(cr, p5, pr, nn, mm);
      add(pr, p7, c11, nn, mm);
      // c12 = p3 + p5
      add(p3, p5, c12, nn, mm);
      // c21 = p2 + p4
      add(p2, p4, c21, nn, mm);
      // c22 = p1 + p3 - p2 + p6
      add(p1, p3, cr, nn, mm);
      subtract(cr, p2, pr, nn, mm);
      add(pr, p6, c22, nn, mm);
      
      free(a11); free(a12); free(a21); free(a22);
      free(b11); free(b12); free(b21); free(b22);
      free(p1); free(p2); free(p3); free(p4);
      free(p5); free(p6); free(p7);
      free(ar); free(br); free(cr); free(pr);
      
      #pragma omp parallel for num_threads(cores)
      for(int j = 0; j < mm; j++){
        for(int i = 0; i < nn; i++){
          Z[j * n + i] = c11[j * nn + i];
          Z[j * n + (i + nn)] = c12[j * nn + i];
          Z[(j + mm) * n + i] = c21[j * nn + i];
          Z[(j + mm) * n + (i + nn)] = c22[j * nn + i];
        }
      }
    }
}

void strassen(double *X, double *Y, double *Z, int n, int p, int m)
{
  int N = pow(2, ceil(log2(n)));
  int P = pow(2, ceil(log2(p)));
  int M = pow(2, ceil(log2(m)));
  
  double *Xp = new double[N * P]();
  double *Yp = new double[P * M]();
  double *Zp = new double[N * M]();
  
  #pragma omp parallel for num_threads(cores)
  for(int i = 0; i < n; i++){
    for(int j = 0; j < p; j++){
      Xp[i * P + j] = X[i * p + j];
    }
  }
  
  #pragma omp parallel for num_threads(cores)
  for(int i = 0; i < p; i++){
    for(int j = 0; j < m; j++){
      Yp[i * M + j] = Y[i * m + j];
    }
  }
  
  int thresh = (N > M) ? N : M;
  thresh = (thresh > P) ? thresh : M;
  
  strassenR(Xp, Yp, Zp, N, P, M, thresh / 8);
  
  #pragma omp parallel for num_threads(cores)
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      Z[i * m + j] = Zp[i * M + j];
    }
  }
}
