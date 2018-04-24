#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define NUMTHREADSPERBLOCK 16

/*** function declarations ***/

void PRINT_MAT(int P, int M, double * matr);

// save matrix to file
void save_gnuplot( double *M, size_t dim );

// evolve Jacobi
__global__  void evolve( double * matrix, double *matrix_new, int dimension );


// return the elapsed time
double seconds( void );

/*** end function declaration ***/




int main(int argc, char* argv[]){

  // timing variables
  double t_start, t_end, increment;

  // indexes for loops
  size_t i, j, it;

  // initialize matrix

  double *matrix, *matrix_new, *tmp_matrix;
  double *d_matrix, *d_matrix_new;
  int dimension = 0, iterations = 0, row_peek = 0, col_peek = 0;
  size_t byte_dimension = 0;

 // check on input parameters

  if(argc != 5) {
    fprintf(stderr,"\nwrong number of arguments. Usage: ./a.out dim it n m\n");
    return 1;
  }

  dimension = atoi(argv[1]);
  iterations = atoi(argv[2]);
  row_peek = atoi(argv[3]);
  col_peek = atoi(argv[4]);

  printf("matrix size = %zu\n", dimension);
  printf("number of iterations = %zu\n", iterations);
  printf("element for checking = Mat[%zu,%zu]\n",row_peek, col_peek);


  if((row_peek > dimension) || (col_peek > dimension)){
    fprintf(stderr, "Cannot Peek a matrix element outside of the matrix dimension\n");
    fprintf(stderr, "Arguments n and m must be smaller than %zu\n", dimension);
    return 1;
  }


  byte_dimension = sizeof(double*) * ( dimension + 2 ) * ( dimension + 2 );
  matrix = ( double* )malloc( byte_dimension );
  matrix_new = ( double* )malloc( byte_dimension );

  memset( matrix, 0, byte_dimension );
  memset( matrix_new, 0, byte_dimension );

  cudaMalloc((void**) &d_matrix, byte_dimension ); //allocating space for d_matrix
  cudaMalloc((void**) &d_matrix_new, byte_dimension );

  //fill initial values  

  for( i = 1; i <= dimension; ++i ){
    for( j = 1; j <= dimension; ++j ){
      matrix[ ( i * ( dimension + 2 ) ) + j ] = 0.5;
    }
  }
	     
  // set up borders 
  increment = 100.0 / ( dimension + 1 );

  
 for( i=1; i <= dimension+1; ++i ){
    matrix[ i * ( dimension + 2 ) ] = i * increment;
    matrix[ ( ( dimension + 1 ) * ( dimension + 2 ) ) + ( dimension + 1 - i ) ] = i * increment;
    matrix_new[ i * ( dimension + 2 ) ] = i * increment;
    matrix_new[ ( ( dimension + 1 ) * ( dimension + 2 ) ) + ( dimension + 1 - i ) ] = i * increment;
  }

  printf("initial matrix\n");
  // PRINT_MAT(dimension+2,dimension+2,matrix);

  // start algorithm
  t_start = seconds();

  cudaMemcpy( d_matrix, matrix, byte_dimension, cudaMemcpyHostToDevice );
  cudaMemcpy( d_matrix_new, matrix_new, byte_dimension, cudaMemcpyHostToDevice );

  dim3 gridDim( (dimension+NUMTHREADSPERBLOCK)/NUMTHREADSPERBLOCK, (dimension+NUMTHREADSPERBLOCK)/NUMTHREADSPERBLOCK );
  dim3 blockDim(NUMTHREADSPERBLOCK , NUMTHREADSPERBLOCK);

  for( it = 0; it < iterations; ++it ){
  
  evolve<<< gridDim, blockDim  >>>( d_matrix, d_matrix_new, dimension );
    //evolve<<< (dimension+NUMTHREADSPERBLOCK)/NUMTHREADSPERBLOCK , NUMTHREADSPERBLOCK >>>( d_matrix, d_matrix_new, dimension );

    // swap the pointers
    tmp_matrix = d_matrix;
    d_matrix = d_matrix_new;
    d_matrix_new = tmp_matrix;
 }

  cudaMemcpy( matrix, d_matrix, byte_dimension, cudaMemcpyDeviceToHost );
  t_end = seconds();

  printf("final matrix\n");
  //PRINT_MAT(dimension+2,dimension+2,matrix);

  printf( "\nelapsed time = %f seconds\n", t_end - t_start );
  printf( "\nmatrix[%zu,%zu] = %f\n", row_peek, col_peek, matrix[ ( row_peek + 1 ) * ( dimension + 2 ) + ( col_peek + 1 ) ] );

  save_gnuplot( matrix, dimension );
  

  free( matrix );
  free( matrix_new );
  cudaFree(d_matrix);
  cudaFree(d_matrix_new);


  return 0;

}

void PRINT_MAT(int P, int M, double * matr){
  for(int j = 0; j < P; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%0.1f ",matr[i+j*M]);
    }
    printf("\n");
  }
}

__global__ void evolve( double * matrix, double * matrix_new, int dimension ){

  /*  __shared__ double * shared_matrix; //pointer to the part of the matrix I want to share

  shared_matrix = ( double* )malloc( NUMTHREADSPERBLOCK * NUMTHREADSPERBLOCK );
  */
  int idx = threadIdx.x + (blockIdx.x * blockDim.x);
  int idy = threadIdx.y + (blockIdx.y * blockDim.y); 
  
  /* if (idx < dimension + 2){
    if(idy < dimension + 2){
      shared_matrix [ idx*(dimension)+idy ] = matrix[ idx*(dimension)+idy ];
    }
  }
  __syncthreads();*/
  
  if (idx>0 && idx<=dimension){
    if(idy>0 && idy<=dimension){
      matrix_new[ ( idx * ( dimension + 2 ) ) + idy ] = ( 0.25 ) * 
	( matrix[ ( ( idx - 1 ) * ( dimension + 2 ) ) + idy ] + 
	  matrix[ ( idx * ( dimension + 2 ) ) + ( idy + 1 ) ] + 	  
	  matrix[ ( ( idx + 1 ) * ( dimension + 2 ) ) + idy ] + 
	  matrix[ ( idx * ( dimension + 2 ) ) + ( idy - 1 ) ] ); 
    }
  }
}

void save_gnuplot( double *M, size_t dimension ){  

  size_t i , j;

  const double h = 0.1;

  FILE *file;

  file = fopen( "solution.dat", "w" );

  for( i = 0; i < dimension + 2; ++i )

    for( j = 0; j < dimension + 2; ++j )

      fprintf(file, "%f\t%f\t%f\n", h * j, -h * i, M[ ( i * ( dimension + 2 ) ) + j ] );

  fclose( file );

}



// A Simple timer for measuring the walltime

double seconds(){

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;

}
