#include "mpi.h"
#include "integral.h"
#include <stdio.h>

static double a = 0.;
static double b = 10000.;
static int n = 1e10;

static double total = 0.;

int main (int argc, char** argv) {
    int R, N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &R);
    MPI_Comm_size(MPI_COMM_WORLD, &N);

    int n_loc = n/N;         // у стількох точках процес рахуватиме значення функції
    double len = (b - a)/N;  // довжина проміжку інтегрування
    double a_loc = a + R*len;
    double b_loc = a_loc + len;
    double integral = integrate(a_loc, b_loc, n_loc);

    MPI_Reduce(&integral, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (R == 0) printf("Integral from %.1f to %.1f = %.3f\n", a, b, total);

    MPI_Finalize();

    return 0;


}