#include "logisticregression.h"

LogisticRegression::LogisticRegression(double **X_, int dim_, double *Y_, double lambda_){
  X = X_;
  dim = dim_;
  Y = Y_;
  lambda = lambda_;
}

double LogisticRegression::objval(double *w_){
  
}