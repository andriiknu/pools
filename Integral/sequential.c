#include "integral.h"
#include <stdio.h>

static double a = 0.;
static double b = 10000.;
static int n = 1e10;

int main () {
    double total = integrate(a, b, n);
    printf("Integral from %.1f to %.1f = %.3f\n", a, b, total);
    return 0;
}
