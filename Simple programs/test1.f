       program main_mpi
       include 'mpif.h'
       integer myid, numprocs, ierr
       call MPI_Init(ierr)
       call MPI_Comm_rank(MPI_COMM_WORLD, myid, ierr)
       call MPI_Comm_size(MPI_COMM_WORLD, numprocs, ierr)
       print *, "process ", myid, " of ", numprocs
       call MPI_Finalize(ierr)
       end program main_mpi
