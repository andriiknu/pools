#include <stdio.h> 
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

double f(double y) {return(4.0/(1.0+y*y));} 

int main(int argc, char** argv) 
{ 
    int N;
    if (argc == 1) {
        N = 10;
    } else if(argc == 2) {
        N = atoi(argv[1]);
    } else {
        printf("U can using only one command line argument - the number of threads\n");
    }

    double w, x, sum, pi; 
    int i; 
    int n = __INT_MAX__; 
    w = 1.0/n; 
    sum = 0.0; 

#ifdef _OPENMP
    printf("U are using OPENMP\n");
    omp_set_num_threads(N);
    omp_set_dynamic(1);
#endif

#pragma omp parallel private(x) shared(w)
{
#ifdef _OPENMP
#pragma omp master
    {
        printf("Number of executed threads: %d\n",omp_get_num_threads());
        printf("Number of availeble processe %d\n", omp_get_num_procs());
    }
#endif
#pragma omp for reduction(+:sum)

    for(i=0; i < n; i++) 
    { 
        x = w*(i-0.5); 
        sum = sum + f(x); 
    } 
}
    pi = w*sum; 
    printf("pi = %.8f\n", pi); 
    printf("pi build-in value = %.8f\n", M_PI);
} 