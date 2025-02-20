#include "../include/TrapezoidRule.hpp"

double TrapezoidRule::integrate(double a, double b, int n, double (*func)(double)){
  double h = (b - a) / n;
  double sum = 0.0;
  
  #pragma omp parallel for reduction(+ : sum)
  for (int i = 1; i < n; i++){
    double x = a + i*h;
    sum += evaluate(func, x);
  }

  return 0.5*h*(evaluate(func, a) + evaluate(func, b) + 2*sum);
}
