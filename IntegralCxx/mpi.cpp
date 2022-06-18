#define REDUCE
// #define TIME_MEASUREMENT


#include "mpi.h"
#include "function.hh"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


static double a = 0.;
static double b = 1.;
static double Icorr = 0.565985876838710;


static double total = 0.;

int main (int argc, char** argv) {
    int R, N;
    int n;
    std::ofstream f("log.txt");


    if (argc == 1) {
        n = 1e6;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("Too few arguments are passed.\nUsage:\nmpirun -np N_OF_PROCESSORS ./build/mpi N_OF_POINTS\n");
    }

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &R);
    MPI_Comm_size(MPI_COMM_WORLD, &N);

    double t_loc = MPI_Wtime();


    int n_loc = n/N;         // у стількох точках процес рахуватиме значення функції
    double len = (b - a)/N;  // довжина проміжку інтегрування
    double a_loc = a + R*len;
    double b_loc = a_loc + len;
    double integral = integrate(a_loc, b_loc, n_loc);



#ifdef REDUCE
    MPI_Reduce(&integral, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
#else
    
    if (R == 0) {
        total = integral;
        for (int r = 1; r < N; ++r) {
            MPI_Recv(&integral, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            total += integral;
        }
    } else {
        MPI_Send(&integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
#endif

    if (R == 0) 
    {
        double time = MPI_Wtime() - t_loc;
        printf("Result = %.16f, Err = %.16f, Time = %.16f\n", total, Icorr - total, time);
        std::ofstream an;
        an.open("analysis.txt", std::ios::app);
        an << N << "\t" << time << "\n";
        an.close();
    }
    
#ifdef TIME_MEASUREMENT

    double t = 0;
    t_loc = MPI_Wtime() - t_loc;
    if (R == 0) {
        f << "rank 0: " << t_loc << std::endl;
        t += t_loc;
        for (int i = 1; i < N; ++i) {
            MPI_Recv(&t_loc, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            f << "rank " << i << ": " << t_loc << "\n";
            t += t_loc;

        }
        f << "Total time = " << t << "\n";
    } else {
        MPI_Send(&t_loc, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
#endif
    



    MPI_Finalize();

    return 0;


}