#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 4

int main( int argc, char * argv[] ){

  double * A;
  int i = 0, loc_size, npes, rank;
  FILE * fp;

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &npes );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  loc_size = SIZE / npes;

  A = (double *) malloc( loc_size * SIZE * sizeof(double) );

  fp = fopen( "matrix.dat", "r" );
  fseek( fp, sizeof(double) * loc_size * SIZE * rank, SEEK_SET );
  fread( A, sizeof(double), loc_size * SIZE, fp );
  fclose( fp );

  free( A );

  MPI_Finalize();

  return 0;
}
