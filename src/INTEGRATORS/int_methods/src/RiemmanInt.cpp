#include "../include/RiemmanInt.hpp"

double RiemannInt::integrate(double a, double b, int n, double (*func)(double)){
  double h = (b - a)/n;
  double sum = 0.0;
  
  #pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++){
    double x = a + (i + 0.5)*h;
    sum += evaluate(func, x);
  }
  return sum*h;
}
