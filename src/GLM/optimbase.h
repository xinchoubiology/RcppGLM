#ifndef OPTIMBASE_H_
#define OPTIMBASE_H_

// optimal problem description
// optimProblem only describes the generalize framework of optimization problem.
// Given that different optimization problem has different kind of input and output form;
// Only virtual problem accessible
class optimProblem{
  public:
    optimProblem();
    ~optimProblem(){};
    virtual double objval(double *x_);
    //dimension return how many predictors in X
    virtual int dimension();
    virtual double* gradient(double *x_);
    virtual double* solve_hessian(double *x_, double *d_);
    virtual double learning_rate(double t);
};

#endif