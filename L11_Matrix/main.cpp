#include <stdio.h> 
#include <string>
#include <omp.h> 

#define PrintResult



#ifdef PrintResult
#include <fstream>
#endif




int main(int argc, char** argv) 
{ 

 double time;
 int num_threads_setted = 12, num_threads_getted, N = 400;
 if (argc > 5) printf("Cmd arguments are not recognized\n");

 for (int i = 1; i < argc ;i += 2) {
    if (std::string(argv[i]) == "-t") {
         num_threads_setted = std::atoi(argv[i+1]);       
    } else if (std::string(argv[i]) == "-N") {
        N = std::atoi(argv[i+1]);
    } 
 }

 
 

 double a[N][N], b[N][N], c[N][N];    
 int i, j, k; 
 
// инициализация матриц
 for (i=0; i<N; i++) 
 for (j=0; j<N; j++) 
 a[i][j]=b[i][j]=i*j; 

 time=omp_get_wtime(); 
 omp_set_num_threads(num_threads_setted);
 omp_set_dynamic(1);
// основной вычислительный блок
 
#pragma omp parallel shared(a, b, c) private(i, j, k) 
{
 #pragma omp master
 {
    num_threads_getted = omp_get_num_threads();
 }
 #pragma omp for
 for(i=0; i<N; i++){ 
 for(j=0; j<N; j++){ 
 c[i][j] = 0.0; 
 for(k=0; k<N; k++) c[i][j]+=a[i][k]*b[k][j]; 
 } 
 } 
}
 time=omp_get_wtime() - time; 
 printf("%d\t%lf\n", num_threads_getted, time); 

#ifdef PrintResult
 std::ofstream of("result.txt");
 if (N < 20)
 {

 for (int i = 0; i < N; ++i)
 {
    for (int j = 0; j < N; ++j) of << c[i][j] << " ";
    of << std::endl;
 }
 }
#endif

}