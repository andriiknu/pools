#include "mpi.h"
#include "stdio.h"

int main (int argc, char** argv) {
  int N, Rank, tmp;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &N);
  MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
  printf("Hello world from process %i \n", Rank);
  MPI_Finalize();
  return 0;
}
