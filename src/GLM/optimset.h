#ifndef OPTIMSET_H_
#define OPTIMSET_H_

#include "optimbase.h"

// optimal problem computing set
class optimSet{
  public:
    optimSet(optimProblem * p, double* x_, int iterate = 100);
    ~optimSet();
    double *x;          // coef Vector
    double *prev_x;     // previous coef Vector
    double *g;          // gradient Vector
    double *prev_g;     // previous gradient Vector
    double f;           // function value of x; f(x)
    double prev_f;      // previous function value of prev_x; f(prev_x)
    double *d;          // direction vector
    double t;           // step-size
    int iter;           // iteration number
    double *f_all;      // keep trajactory of function value
    double **x_all;     // keep trajactory of coef Vector (iter x dim) matrix
    double **g_all;     // keep trajactory of gradient Vector
    double **d_all;     // keep trajactory of direction Vector
    double *t_all;       // keep trajactory of step-size value 
};

#endif