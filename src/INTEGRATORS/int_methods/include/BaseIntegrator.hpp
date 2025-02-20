#ifndef BASEINTEGRATOR_HPP
#define BASEINTEGRATOR_CPP

#ifdef __OPENMP
#include <omp.h>
#endif

class BaseIntegrator {
  public:

    virtual ~BaseIntegrator() = default
    virtual double integrate(double a, double b, int n, double (*func)(double)) = 0;

  protected:
    double evaluate(double (*func)(double), double x);
};
#endif //BASEINTEGRATOR_HPP
