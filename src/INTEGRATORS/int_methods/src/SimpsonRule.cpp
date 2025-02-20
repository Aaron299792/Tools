#include "../include/SimpsonRule.hpp"

SimpsonRule::integrate(double a, double b, int n, double (*func)(double)){
  double h = (b - a)/ n;
  double sumodd = 0.0;
  double sumeven = 0.0;
  
  #pragma omp parallel for reduction(+ : sumodd)
  for (int i = 1; i < n; i += 2){
    double x = a + i*h;
    sumodd += evaluate(func, x);
  }
  #pragma omp parallel for reduction(+ : sumeven)
  for (int j = 2; j < n; j += 2){
    double x = a + j*h;
    sumeven += evaluate(func, x);
  }

  return (h/3)*(evaluate(func, a) + evaluate(func, b) + 4*sumodd + 2*sumeven);
}
