#include <stdlib.h>
#include <stdio.h>

#define SIZE 4096

int main( int argc, char * argv[] ){

  double * A, ttime;
  int i = 0;
  FILE * fp;

  A = (double *) malloc( SIZE * SIZE * sizeof(double) );

  for( i = 0; i < SIZE * SIZE; i++ ){

    A[i] = (double) ( rand() % 1000 + 1 );
  }

  fp = fopen( "matrix.dat", "w" );
  fwrite( A, sizeof(double), SIZE * SIZE, fp );
  fclose( fp );

  free( A );

  return 0;
}
