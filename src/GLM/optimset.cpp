#include "optimset.h"

optimSet::optimSet(optimProblem * p, double* x_, 
                   int iterate = 100){
  int dim = p.dimension();
  x = x_;
  prev_x = new double[dim];
  g = p.gradient(x);
  prev_g = new double[dim];
  f = p.objval(x);
  prev_f = p.objval(prev_x);
  d = new double[dim];
  t = 0.0;
  iter = iterate;
  // keep optimal problem's trajactory
  f_all = new double[iter + 1];
  t_all = new double[iter + 1];
  x_all = new double*[iter + 1];
  g_all = new double*[iter + 1];
  d_all = new double*[iter + 1];
  for(int i = 0; i < iter + 1; i++){
    x_all[i] = new double[dim];
    g_all[i] = new double[dim];
    d_all[i] = new double[dim];
  }
}

optimSet::~optimSet(){
  delete[] f_all;
  delete[] t_all;
  for(int i = 0; i < iter + 1; i++){
    delete[] x_all[i];
    delete[] g_all[i];
    delete[] d_all[i];
  }
  delete[] x_all;
  delete[] g_all;
  delete[] d_all;
}

