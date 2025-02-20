#include "../include/BaseIntegrator.hpp"

double BaseIntegrator::evaluate(double (*func)(double), double x) {
  return func(x);
}
