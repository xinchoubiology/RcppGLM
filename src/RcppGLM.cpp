#include "RcppGLM.h"

NumericMatrix DGEMM(SEXP xs, SEXP ys){
  double * X = as<double*>(xs);
  double * Y = as<double*>(ys);
  // Dimension xs & ys
  NumericMatrix xx(xs);
  NumericMatrix yy(ys);
  int n = xx.nrow(), m = yy.ncol();
  
  if(xx.ncol() != yy.nrow()){
    stop("invalid dimenstion of matrices");
  }
  int p = xx.ncol();
  // Result matrix Z 
  double * Z = new double[m * n];
  
  // Initialization
  // memset(Z, 0, sizeof(double) * m * n);
  
  // Matrix production 
  dgemm_block(X, Y, Z, n, p, m);
  NumericMatrix zz = wrap(Z, n, m);
  
  return zz;
}

NumericMatrix DMM(SEXP xs, SEXP ys){
  double * X = as<double*>(xs);
  double * Y = as<double*>(ys);
  // Dimension xs & ys
  NumericMatrix xx(xs);
  NumericMatrix yy(ys);
  int n = xx.nrow(), m = yy.ncol();
  
  if(xx.ncol() != yy.nrow()){
    stop("invalid dimenstion of matrices");
  }
  int p = xx.ncol();
  // Result matrix Z 
  double * Z = new double[m * n];
  
  // Initialization
  memset(Z, 0, sizeof(double) * m * n);
  
  
  // Matrix production 
  dgemm(X, Y, Z, n, p, m);
  NumericMatrix zz = wrap(Z, n, m);
  
  return zz;
}


NumericMatrix dgemm_blas(NumericMatrix xs, NumericMatrix ys){
  double alpha = 1.0;
  double beta  = 0.0;
  bool tx = false;
  bool ty = false;
  // get row and col of xs and ys
  int xrow = tx ? xs.ncol() : xs.nrow();
  int xcol = tx ? xs.nrow() : xs.ncol();
  int yrow = ty ? ys.ncol() : ys.nrow();
  int ycol = ty ? ys.nrow() : ys.ncol();
  
  NumericMatrix zs(xrow, ycol);
  
  double * X = as<double*>(xs);
  double * Y = as<double*>(ys);
  double * Z = as<double*>(zs);
  
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, xrow, ycol, xcol, alpha, X, xcol, Y, yrow, beta, Z, xrow);
  
  NumericMatrix zz = wrap(Z, xrow, ycol);
  
  return zz;
}

NumericMatrix dgeqr_lapack(NumericMatrix x){
  double * X = as<double*>(x);
  
  int M = x.nrow();
  int N = x.ncol();
  int lda = M;
  double * tau = new double[std::min(M, N)]; 
  int lwork = -1;
  double * work = new double[std::max(1, lwork)];
  int info;
  dgeqrf_(&M, &N, X, &lda, tau, work, &lwork, &info);
  
  NumericMatrix qr = wrap(X, M, N);
  
  return qr;
}


NumericMatrix strassenMM(SEXP xs, SEXP ys){
  double * X = as<double*>(xs);
  double * Y = as<double*>(ys);
  // Dimension xs & ys
  NumericMatrix xx(xs);
  NumericMatrix yy(ys);
  int n = xx.nrow(), m = yy.ncol();
  
  if(xx.ncol() != yy.nrow()){
    stop("invalid dimenstion of matrices");
  }
  int p = xx.ncol();
  // Result matrix Z 
  double * Z = new double[m * n];
  
  // Initialization
  // memset(Z, 0, sizeof(double) * m * n);
  
  // Matrix production 
  strassen(X, Y, Z, n, p, m);
  NumericMatrix zz = wrap(Z, n, m);
  
  return zz;
}
