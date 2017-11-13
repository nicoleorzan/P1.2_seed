#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define SIZE 4096

int main( int argc, char * argv[] ){

  double * A;
  int i = 0, loc_size, npes, rank;
  FILE * fp;

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &npes );
  MPI_Comm_size( MPI_COMM_WORLD, &rank );

  loc_size = SIZE / npes;

  A = (double *) malloc( loc_size * SIZE * sizeof(double) );

  for( i = 0; i < loc_size * SIZE; i++ ){

    A[i] = (double) ( rand() % 1000 + 1 );
  }

  fp = fopen( "matrix.dat", "w" );
  fseek( fp, sizeof(double) * loc_size * SIZE * rank, SEEK_SET );
  fwrite( A, sizeof(double), loc_size * SIZE, fp );
  fclose( fp );

  free( A );

  MPI_Finalize();

  return 0;
}
