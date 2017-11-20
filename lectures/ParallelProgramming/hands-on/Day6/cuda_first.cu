#include<stdio.h>
#include<assert.h>

//cudaMemcpy( dest, source, sizeinbytes, cudaMemcpyHostToDevice | cudaMemcpyDeviceToHost );
//cudaMalloc( (void **) &my_ptr, sizeinbytes );

#define SIZE 12 //0000000
#define NUM_THREADS 512

__global__ void add( int * d_a, int * d_b, int * d_c )
{
  int idx = threadIdx.x + (blockIdx.x * blockDim.x );
  if( idx < SIZE )
    d_c[idx] = d_a[idx] + d_b[idx];
}


int main()
{
  int * h_a, * h_b, * h_c;
  int * d_a, * d_b, * d_c;
  int i;
  size_t size_in_bytes = SIZE * sizeof(int);

  h_a = (int *) malloc( size_in_bytes );
  h_b = (int *) malloc( size_in_bytes );
  h_c = (int *) malloc( size_in_bytes );

  cudaMalloc( (void **) &d_a, size_in_bytes );
  cudaMalloc( (void **) &d_b, size_in_bytes );
  cudaMalloc( (void **) &d_c, size_in_bytes );

  for( i = 0; i < SIZE; i++ ){
    h_a[i] = 1;
    h_b[i] = 2;
  }

  cudaMemcpy( d_a, h_a, size_in_bytes, cudaMemcpyHostToDevice );
  cudaMemcpy( d_b, h_b, size_in_bytes, cudaMemcpyHostToDevice );

  add<<< ( SIZE + NUM_THREADS ) / NUM_THREADS, NUM_THREADS >>>( d_a, d_b, d_c );

  cudaMemcpy( h_c, d_c, size_in_bytes, cudaMemcpyDeviceToHost );  

  if( SIZE < 100 ){
    for( i = 0; i < SIZE; i++)
      fprintf( stdout, " %d", h_c[i] );
  }
  
  free( h_c );
  free( h_b );
  free( h_a );

  cudaFree( d_a );
  cudaFree( d_b );
  cudaFree( d_c );

  return 0;

}
