#include "function.hh"
#include <stdio.h>
#include <stdlib.h>

static double a = 0.;
static double b = 1.;
static double Icorr = 0.565985876838710;


int main (int argc,char** argv) {
    int n;
    if (argc == 1) {
        n = 1e6;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("Too few arguments are passed.\n");
    }
    double total = integrate(a, b, n);
    printf("Integral from %.1f to %.1f = %.16f\nDeviation = %.16f\n", a, b, total, Icorr - total);
    return 0;
}
