#ifndef __LOGISTICREGRESSION_H_
#define __LOGISTICREGRESSION_H_

#include "optimbase.h"

class LogisticRegression :: public optimProblem{
  public:
    LogisticRegression(double **X_, int dim_, double *Y_, double lambda_);
    ~LogisticRegression(){};
    double objval(double *w_);
    //dimension return how many predictors in X
    int dimension();
    double* gradient(double *w_);
    double* solve_hessian(double *w_, double *d_);
    
  private:
    int dim;         // predictors dimension
    double **X;      // predictors matrix
    double *Y;       // response vector
    double lambda;   // lambda parameter for regularizer
}

#endif