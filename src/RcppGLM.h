#ifndef RCPPGLM_H_
#define RCPPGLM_H_

#include "RcppGLMAs.h"
#include "GLM/dgemm.h"
#include "GLM/strassen.h"
#include <cblas.h>
#include <clapack.h>
#include <Rcpp.h>

using namespace Rcpp;

//' @title DGEMM
//' @param xs Matrix X
//' @param ys Matrix Y
//' @return zs Result Matrix Z
//' @export
// [[Rcpp::export]]
NumericMatrix DGEMM(SEXP xs, SEXP ys);


//' @title DMM
//' @param xs Matrix X
//' @param ys Matrix Y
//' @return zs Result Matrix Z
//' @export
// [[Rcpp::export]]
NumericMatrix DMM(SEXP xs, SEXP ys);

//' @title dgemm_blas
//' @param xs Matrix X
//' @param ys Matrix Y
//' @return zs Result Matrix Z
//' @export
// [[Rcpp::export]]
NumericMatrix dgemm_blas(NumericMatrix xs, NumericMatrix ys);

//' @title dgeqr_lapack
//' @param x Matrix X to be
//' @return x
//' @export
// [[Rcpp::export]]
NumericMatrix dgeqr_lapack(NumericMatrix x);

//' @title strassenMM
//' @param xs Matrix x
//' @param ys Matrix y
//' @return zs Result Matrix
//' @export
// [[Rcpp::export]]
NumericMatrix strassenMM(SEXP xs, SEXP ys);



#endif
