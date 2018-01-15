#include<stdio.h>
#include<assert.h>

#define N 4 //size of the matrix in one dimension
#define THREADSPERBLOCK 4

void PRINT_MAT(int P, int M, double * matr){
  for(int j = 0; j < P; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%f ",matr[i+j*M]);
    }
    printf("\n");
  }
}

__global__ void transpose( double * d_A, double * d_AT ){
  int idx = threadIdx.x + (blockIdx.x * blockDim.x);
  int i = idx/N;
  int j = idx%N;
  
  if (idx<N*N)  d_AT[i+j*N] = d_A[j+i*N];
}
  
  
  
  int main(){
    
    double * h_A, * h_AT;
    double * d_A, * d_AT;
    size_t matsize = N * N * sizeof(double); //long integer
    int nblocks = ((N*N)+THREADSPERBLOCK)/THREADSPERBLOCK;
    
    h_A = (double *) malloc( matsize );
    h_AT = (double *) malloc( matsize );
    
    cudaMalloc((void**) &d_A, matsize );
    cudaMalloc((void**) &d_AT, matsize );
    
    for(int i=0;i<N*N;i++){
      h_A[i]=(double )i;
      h_AT[i]=0.;
    }
    
    printf("initial matrix:\n");
    PRINT_MAT(N,N,h_A);
    
    cudaMemcpy( d_A, h_A, matsize, cudaMemcpyHostToDevice );
    cudaMemcpy( d_AT, h_AT, matsize, cudaMemcpyHostToDevice );
    transpose<<< nblocks, THREADSPERBLOCK >>>( d_A , d_AT );
    cudaMemcpy( h_AT, d_AT, matsize, cudaMemcpyDeviceToHost );

    printf("transpose matrix:\n");
    PRINT_MAT(N,N,h_AT);
    
    free(h_A);
    free(h_AT);
    
    cudaFree(d_A);
    cudaFree(d_AT);
    
    return 0;
    
  }
