PROGRAM TRANSPOSE
!
!  Copyright (C) 2001-2014 The Abdus Salam, International Centre of Theoretical Physics (ICTP)
! 
! This file is distributed under the terms of the GNU General Public License. 
! See http://www.gnu.org/copyleft/gpl.txt 
! 
! The code is the solution for the exercise D2-exercise2 of the course P1.2 - Master in HPC @SISSA/ICTP
! 
! Example of code for Matrix transpose with dynamic allocation
!
! Author: Ivan Girotto
! Revised by: G.P. Brandino and M. Atambo
! Last update: OCT-2014
! 
!

  IMPLICIT NONE

  INTEGER *4 :: matrixdim  ,  arg_count, bdim
  CHARACTER( len = 8 ) :: arg1, arg2
  REAL*8, ALLOCATABLE, DIMENSION( :, : ) :: A, AT, BUF
  INTEGER*4 :: i, j, mb, nb, ioff, joff, ib, jb, nblocks, count = 0.0
  REAL*8 :: temp, t_start, t_stop,bswap
  REAL * 8 ::  cclock
  EXTERNAL cclock

  ! Minimal instructions for reading the matrix size 
  arg_count = command_argument_count( )
  IF( arg_count .LT. 1 ) THEN
     WRITE( *, * ) "usage: $EXECUTABLE [MATRIXDIM]"
     CALL exit( 1 )
  END IF

  CALL get_command_argument( 1, arg1 )
  READ( arg1 , * ) matrixdim
  CALL get_command_argument( 2, arg2 )
  READ( arg2 , * ) bdim
  
  !Allocation of the  Matrix memory
  ALLOCATE( A( matrixdim, matrixdim ) )
  ALLOCATE( AT( matrixdim, matrixdim ) )
  ALLOCATE( BUF( bdim, bdim ) )
  
  !Initialization of the sample matrix 
  DO j = 1, matrixdim
     DO i = 1, matrixdim
        A( i, j ) = DBLE( count )
        count = count + 1
   END DO
  END DO

  nblocks = matrixdim/bdim
  print*,nblocks
  !Implement loops over the blocks of the main Matrices
  call cpu_time(t_start)
  DO i=0,3
     print*,i
  END DO
  
  DO ib = 1, nblocks
     ioff = (ib-1)*bdim
     DO jb = 1, nblocks
        joff = (jb-1)*bdim
        ! I fill the block
        DO j=1,bdim
           DO i=1,bdim
              BUF(i,j) = A(i+ioff,j+joff)
           END DO
        END DO
        ! swap the block 
        DO j=1,bdim
           DO i=1,j-1 !j-2
              bswap = BUF(i,j)
              BUF(i,j)=BUF(j,i)
              BUF(j,i)=bswap
           END DO
        END DO
        !fill the transpose matrix
        DO i=1,bdim
           DO j=1,bdim
              AT(j+joff,i+ioff)=BUF(j,i)
           END DO
        END DO
     END DO
  END DO
  
  call cpu_time(t_stop)

  WRITE( * , * ) 'Time to perform transpose: ', t_stop - t_start, '(seconds)'

  DEALLOCATE( A )
  DEALLOCATE( AT )
  DEALLOCATE( BUF )
  
END PROGRAM TRANSPOSE
  
