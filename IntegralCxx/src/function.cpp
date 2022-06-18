#include "function.hh"
#include "math.h"

double f (double x) {
    double res = pow(x, 3) + x;
    res /= pow(x, 4) + 1;
    return res;
}



double integrate(double a, double b, int n) {
    return integrate(a, b, n, &f);
}