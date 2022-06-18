#include "integral.h"

double f (double x) 
{
    return x*x+x+1;
}

double integrate(double a, double b, int n)
{
    double res;
    double h;
    int i;

    h = (b - a)/n;
    res = (f(a) + f(b))*(h/2);
    for (i = 1; i < n; ++i)
        res += f(a+i*h)*h;
    return res;

}
