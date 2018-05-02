#include<stdio.h>
#include<assert.h>

#define N 4
#define THREADSPERBLOCK 4

__global__ void matmult( double * d_A, double * d_B, double * d_C ){

  __shared__ double Arow[N];

  int idx = threadIdx.x + blockIdx.x * blockDim.x;
  if(idx<N*N){
    Arow[threadIdx.x]=d_A[idx];
  }
  __syncthreads();

  for(int  k = 0; k < N; k++ ) {
     d_C[idx] += Arow[k] *d_B[k * N + threadIdx.x];
   }

}

void PRINT_MAT(int P, int M, double * matr){
  for(int j = 0; j < P; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%f ",matr[i+j*M]);
     }
    printf("\n");
  }
}


int main(){
  
  double * h_A , * h_B, * h_C;
  double * d_A , * d_B, * d_C;
  size_t matsize = N * N * sizeof(double); //long integer
  
  h_A = (double *) malloc( matsize );
  h_B = (double *) malloc( matsize );
  h_C = (double *) malloc( matsize );
  
  cudaMalloc((void**) &d_A, matsize );
  cudaMalloc((void**) &d_B, matsize );
  cudaMalloc((void**) &d_C, matsize );
  
  for(int i=0;i<N*N;i++){
    h_A[i]=( rand() % 100 + 1 );// (double )i;
    h_B[i]=( rand() % 100 + 1 ); //(double )i;
    h_C[i]=0.;
  }
  
  printf("matrice A:\n");  
  PRINT_MAT(N,N,h_A);
  printf("matrice B:\n");
  PRINT_MAT(N,N,h_B);

  cudaMemcpy( d_A, h_A, matsize, cudaMemcpyHostToDevice );
  cudaMemcpy( d_B, h_B, matsize, cudaMemcpyHostToDevice );
  cudaMemcpy( d_C, h_C, matsize, cudaMemcpyHostToDevice );

  dim3 blockDim(THREADSPERBLOCK, THREADSPERBLOCK);
  dim3 gridDim((N*N)/THREADSPERBLOCK, (N*N)/THREADSPERBLOCK);
  matmult<<< gridDim, blockDim >>>( d_A, d_B, d_C);
  cudaMemcpy( h_C, d_C, matsize, cudaMemcpyDeviceToHost );
  
  printf("matrice C=A*B:\n");
  PRINT_MAT(N,N,h_C);
  
  free(h_A);
  free(h_B);
  free(h_C);
  
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  
  return 0;
  
}
