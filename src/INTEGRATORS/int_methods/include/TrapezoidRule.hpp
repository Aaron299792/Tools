#ifndef TRAPEZOIDRULE_HPP
#define TRAPEZOIDRULE_HPP
#include "BaseIntegrator.hpp"

class TrapezoidRule : public BaseIntegrator {
  public:
    double integrate(double a, double b, int n, double (*func)(double)) override;
}

#endif
