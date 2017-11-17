#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#include "mkl.h"

#define SIZE 1024

double seconds(){

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

int main( int argc, char *argv[] ){

  int rank, nprocs, dest, source;

  int i = 0, j = 0, k = 0, j_global = 0, size_loc = 0, count = 0, count_b = 0, n_block;
  size_t size_in_bytes;

  double *A, *B, *C, *C_block, *A_block, *B_tmp, *B_buff;
  double t_start, t_mine, t_slowest, t_start_comp, t_comp = 0, t_slowest_comp, t_start_comm, t_comm = 0, t_slowest_comm;

#ifdef __DEBUG
  double *A_Global, *B_Global, *C_Global, *C_Parallel;
#endif

  MPI_Request request[2];

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &nprocs );

  dest = ( rank + nprocs - 1 ) % nprocs;
  source = ( rank + 1 ) % nprocs;
  
  size_loc = SIZE / nprocs ;

  size_in_bytes = size_loc * SIZE * sizeof(double);

  A = (double *) malloc( size_in_bytes );
  B = (double *) malloc( size_in_bytes );
  B_buff = (double *) malloc( size_in_bytes );
  C = (double *) malloc( size_in_bytes );

  // Initialization of matrices A and B to random values 
  for( i = 0; i < size_loc * SIZE; i++ ){

    A[i] = (double) (rand() % 100);
    B[i] = (double) (rand() % 100);
    
  }
  memset( C, 0, size_in_bytes );

  t_start = seconds();

  for( count = 0; count < nprocs; count++ ){
    
    MPI_Isend( B, size_loc * SIZE, MPI_DOUBLE, dest, rank, MPI_COMM_WORLD, &request[1] );
    MPI_Irecv( B_buff, size_loc * SIZE, MPI_DOUBLE, source, source, MPI_COMM_WORLD, &request[0] );

    t_start_comp = seconds();  

    n_block = ( rank + count ) % nprocs; 
    A_block = A + ( n_block * size_loc );

    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, size_loc, SIZE, size_loc, 1.0, A_block, SIZE, B, SIZE, 1.0, C, SIZE );
    t_comp += seconds() - t_start_comp;           

    t_start_comm = seconds();      
    MPI_Waitall( 2, request, MPI_STATUSES_IGNORE );
    t_comm += seconds() - t_start_comm; 

    B_tmp = B_buff;
    B_buff = B;
    B = B_tmp;

  } 
  t_mine = seconds() - t_start;

  MPI_Reduce( &t_mine, &t_slowest, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
  MPI_Reduce( &t_comp, &t_slowest_comp, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
  MPI_Reduce( &t_comm, &t_slowest_comm, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD );


#ifdef __DEBUG
      
  if( !rank){
    A_Global = (double *) malloc( SIZE * SIZE * sizeof(double) );
    B_Global = (double *) malloc( SIZE * SIZE * sizeof(double) );
    C_Global = (double *) malloc( SIZE * SIZE * sizeof(double) );
    C_Parallel = (double *) malloc( SIZE * SIZE * sizeof(double) );
  }  

  MPI_Gather( A, SIZE * size_loc, MPI_DOUBLE, A_Global, SIZE * size_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather( B, SIZE * size_loc, MPI_DOUBLE, B_Global, SIZE * size_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather( C, SIZE * size_loc, MPI_DOUBLE, C_Parallel, SIZE * size_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if( !rank ){    

    memset( C_Global, 0, size_in_bytes );  
  
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A_Global, SIZE, B_Global, SIZE, 0.0, C_Global, SIZE);

    for( i = 0; i < size_loc; i++){
      for( j = 0; j < size_loc; j++){
	  
	count = ( i * SIZE ) + j;
	  
	if( C_Global[count] != C_Parallel[count] ){
	    
	  fprintf( stderr, "\n\tProgramm Error! C_Parallel[%d][%d] != C_Global[%d][%d] => %.20g != %.20g ...\n\n", i, j, i, j, C_Parallel[count], C_Global[count] );
	  MPI_Abort( MPI_COMM_WORLD, 1 );
	}
      }
    }
      
    free ( A_Global );
    free ( B_Global );
    free ( C_Global );
    free ( C_Parallel );

  }
#endif
  
  if( !rank ){
    fprintf( stdout, "\n\tParallel DGEMM Completed Succesfully! \n" );
    fprintf( stdout, "\tTime to solution of %.3g seconds for SIZE = %d \n", t_slowest, SIZE );
    fprintf( stdout, "\tTime of computation %.3g seconds for SIZE = %d \n", t_slowest_comp, SIZE );
    fprintf( stdout, "\tTime of communication %.3g seconds for SIZE = %d \n\n", t_slowest_comm, SIZE );
  }
  
  free( A );
  free( B );
  free( C );
  free( B_buff );
  
  MPI_Finalize();
  
  return 0;
}
  
