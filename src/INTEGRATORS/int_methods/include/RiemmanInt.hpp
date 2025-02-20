#ifndef RIEMANNINT_HPP
#define RIEMANNINT_HPP
#include "BaseIntegrator.hpp"

class RiemannInt : public BaseIntegrator {
  public:
    double integrate(double a, double b, int n, double (*func)(double)) override;
};

#endif //RIEMANN_HPP
