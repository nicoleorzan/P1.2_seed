#include <stdlib.h>
#include <stdio.h>

#define SIZE 4

int main( int argc, char * argv[] ){

  double * A, ttime;
  int i = 0;
  FILE * fp;

  A = (double *) malloc( SIZE * SIZE * sizeof(double) );

  fp = fopen( "matrix.dat", "r" );
  fread( A, sizeof(double), SIZE * SIZE, fp );
  fclose( fp );

  free( A );

  return 0;
}
