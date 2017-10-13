PROGRAM to_be_improved
  IMPLICIT NONE

  INTEGER :: i,j
  INTEGER, PARAMETER :: n=1000, m=1000
  REAL(KIND=8) ::  a(n,m), b(n,m)
  REAL(KIND=8) ::  t1,t2

  CALL cpu_time(t1)
  DO I=1, 1000
     DO J=1, 1001
        A(I,J) = I + J
     ENDDO
  ENDDO
  CALL cpu_time(t2)
  
  PRINT*,'total time=',t2-t1
END PROGRAM to_be_improved
