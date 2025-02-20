#ifndef SIMPSONRULE_HPP
#define SIMPSONRULE_HPP
#include "BaseIntegrator.hpp"

class SimpsonRule : public BaseIntegrator {
  public:
    double integrate(double a, double b, int n, double (*func)(double)) override;
}

#endif
