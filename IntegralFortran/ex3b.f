       Program Example3b
       Implicit None
       Include 'mpif.h'
       Integer Size, Rank, Ierr, I, N, Status(MPI_STATUS_SIZE)
       Double Precision Sum, GSum, A, B, time1, time2, Icorr,
     &Al, Bl, X, F, ISum, Integral
C      Пределы интегрирования
       Parameter (A=0.d0, B=1.d0, Icorr = 0.565985876838710)
C      Подынтегральная функция
       
       Call MPI_INIT(Ierr)
       Call MPI_COMM_SIZE(MPI_COMM_WORLD, Size, Ierr)
       Call MPI_COMM_RANK(MPI_COMM_WORLD, Rank, Ierr)
C      «0»-процесс засекает время
       If (Rank.eq.0) time1 = MPI_WTime()
C        Каждый процесс определяет свои пределы интегрирования
C        и число интервалов разбиения
         Al = A+(B-A)*Rank/Size
         Bl = Al+(B-A)/Size
         N = 10000000/Size
C        Каждый процесс определяет свою частичную сумму по маленьким интревалам...
         Sum = Integral(Al, Bl, N)
C        «0»-процесс получает частичные суммы и определяет результат
         If (Rank.eq.0) Then
           GSum = Sum
           Do I=1,Size-1
             Call MPI_RECV(ISum, 1, MPI_DOUBLE_PRECISION,
     &       MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, Status, Ierr)
             GSum = GSum + ISum
           End Do
         time2 = MPI_WTime()
         Write (6,*) 'Result= ',GSum,' Error= ',Icorr-GSum,
     &               ' Time=',time2 - time1
       else
         Call MPI_SEND(Sum, 1, MPI_DOUBLE_PRECISION, 0,
     &                         0, MPI_COMM_WORLD, Ierr)
       End If
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