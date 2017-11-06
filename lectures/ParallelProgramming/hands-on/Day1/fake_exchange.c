/*
 * This code is an example of data exchange using MPI blocking send/recv
 * The example is made for course p1.2 of MHPC and is NOT meant for production.
 * The implementation might be inefficient or wrong for teaching purpose. 
 * 
 * Created by I. Girotto (i.girotto@ictp.it)
 * Last revision: Nov 2017
 */

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 100000
#define MPI_TAG 10

int main(int argc, char * argv[] ){

  double * send, * recv;
  
  int rank, size, mate;
  int i;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if( rank ) mate = 0;
  else mate = 1;

  send = (double *) malloc( SIZE * sizeof(double) );
  for( i = 0; i < SIZE; i++ ) send[ i ] = (double) rank;

  MPI_Send( send, SIZE, MPI_DOUBLE, mate, MPI_TAG, MPI_COMM_WORLD );

  recv = (double *) malloc( SIZE * sizeof(double) );
  for( i = 0; i < SIZE; i++ ) recv[ i ] = (double) rank;
    
  fprintf( stdout, "\nBefore receive - I am process %d. Buffer value = %.3g", rank, recv[ 0 ] ); 
  MPI_Recv( recv, SIZE, MPI_DOUBLE, mate, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
  fprintf( stdout, "\nAfter receive - I am process %d. Buffer value = %.3g \n\n", rank, recv[ 0 ] ); 

  MPI_Finalize();
  
  return 0;

}
