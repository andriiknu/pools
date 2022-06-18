#include "integral.hh"

//метод трапецій
double integrate(double a, double b, int n, double (*f)(double))
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





