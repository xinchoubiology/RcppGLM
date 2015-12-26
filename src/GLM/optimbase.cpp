#include "optimbase.h"

double optimProblem::objval(double *x_){
  std::cerr << "return the objective function value at x";
}

int optimProblem::dimension(){
  std::cerr << "return dimension of the variable";
}

double* optimProblem::gradient(double *x_){
  std::cerr << "return the gradient at x"; 
}

double* optimProblem::solve_hessian(double *x_, double *d_){
  std::cerr << "solve the hessian at x and store it in d";
}

double optimProblem::line_search(double *x_, double *d_){
  std::cerr << "compute exact line search at x in direction d";
}

virtual double optimProblem::learning_rate(double t){
  return 1.0 / (1.0 + t);
}

