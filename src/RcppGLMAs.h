#ifndef RCPPGLM_RCPPGLMAS_H_
#define RCPPGLM_RCPPGLMAS_H_

#include <vector>
#include <RcppCommon.h>
#include <omp.h>

#define core omp_get_max_threads()

namespace Rcpp {
template <> double* as(SEXP x) {
    SEXP dim = Rf_getAttrib( x, R_DimSymbol ) ;
    int nrow = INTEGER(dim)[0];
    int ncol = INTEGER(dim)[1];
    double * res = REAL(x);
    // X %*% Y = t(t(Y) %*% t(X))
    return res;
}
}

#include <Rcpp.h>

namespace Rcpp {

template <typename T>
NumericMatrix wrap(T * m , int nrow, int ncol) {

    std::vector<T> vec(&m[0], &m[nrow * ncol]);
    
    NumericVector output = wrap(vec);
    
    output.attr("dim") = Dimension(nrow, ncol);    

    return wrap(output);
}
}

#endif
