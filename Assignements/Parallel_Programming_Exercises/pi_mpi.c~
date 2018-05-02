#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

//#define SIZE 100
#define MPI_TAG 10

int main(int argc, char * argv[]){

  long n , i ; 
  double  w, x, partial_sum, pi, interval, finalpi;
  int rank, size;

  n = 100000000;
  partial_sum = 0.0;
  w = 1.0/n;
  
  MPI_Init(&argc, &argv); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  interval = 1.0/size;

  // if (rank) printf("size=%i\n",size);
  
  for ( i = rank*n*interval ; i <= (rank+1)*n*interval ; i++ ) {
      x =  w * (i - 0.5);
      partial_sum = partial_sum + (4.0 / (1.0 + x * x ) );
  }
  
  MPI_Reduce(&partial_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  finalpi = w * pi;

  if (rank == 0) printf("Final pi: %.16g\n", finalpi);
  
  MPI_Finalize();
  
  return 0;
}
