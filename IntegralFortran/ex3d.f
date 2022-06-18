       Program Example3d
       Implicit None
       Include 'mpif.h'
       Integer Size, Rank, Ierr, I, N, u, Status(MPI_STATUS_SIZE)
       Double Precision Integral, S, GS, A, B, Al, 
     & Bl, X, F, Icorr, Len, time_loc, time
       
      
       Parameter (A=0.d0, B=1.d0, Icorr = 0.565985876838710, u = 20) 


       Call MPI_INIT(Ierr)
       Call MPI_COMM_SIZE(MPI_COMM_WORLD, Size, Ierr)
       Call MPI_COMM_RANK(MPI_COMM_WORLD, Rank, Ierr)

       
       
       If (Rank.eq.0) Then
         READ(*,*)N
         N = N/Size
         
c          do i=1, Size-1
c            mpi_send(N, 1, mpi_double_precision,)
       end if
       call MPI_Barrier(MPI_Comm_world, Ierr)
       time_loc = mpi_wtime()
       Len = (B-A)/Size
       Al = A+Rank*Len
       Bl = Al+Len
       
       call mpi_bcast(N, 1, mpi_integer, 0, 
     & mpi_comm_world, Ierr)

       S = Integral(Al, Bl, N)

       Call MPI_REDUCE(S, GS, 1, MPI_DOUBLE_PRECISION, MPI_SUM, 
     & 0, MPI_COMM_WORLD, Ierr)

       

       time_loc = MPI_WTime() - time_loc


      open(u, file = 'time.out')

       If (Rank.eq.0) Then 

         Write (6,*) 'Result=',GS,' Error=',Icorr-GS,' Time=',time_loc

        write(u, *) 'Rank',Rank,': time=',time_loc

         time = time_loc
         do i = 1, Size-1
          call mpi_recv(time_loc, 1, mpi_double_precision, i, 0, 
     &    mpi_comm_world, Status, ierr)

          write(u,*)'Rank',i,': time=', time_loc

           time = time + time_loc
         end do

        WRITE(u,*)'Total time=',time

      else
        call mpi_send(time_loc, 1, mpi_double_precision, 0, 0, 
     &  mpi_comm_world, ierr)  
       End If
      close(u)



       Call MPI_FINALIZE(Ierr)
       Stop
       End


       DOUBLE PRECISION function F(x)
       DOUBLE PRECISION x
       F = (x**3 + x) / (x**4 + 1)
       RETURN
       end


       DOUBLE PRECISION function Integral(a, b, n)
       DOUBLE PRECISION a, b, h, F
       INTEGER n, i
       h = (b - a)/n
       Integral = (F(a) + F(b))*(h/2)
       do i = 1, n-1
         Integral = Integral + f(a+i*h)*h
       end do
       RETURN
       end
       
