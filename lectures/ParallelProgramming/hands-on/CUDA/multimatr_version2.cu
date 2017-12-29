#include<stdio.h>
#include<assert.h>

#define N 4096
//#define NUM_THREADS 512
#define BK_SIZE 512

__global__ void matmult( double * d_A, double * d_B, double * d_C )
{
  __shared__ double Arow[N];
  
  int idx = threadIdx.x;
  int idy = blockIdx.y;
  while(idy<N){
    Arow[idy]=d_A[idy+N*idx];
    idy+=blockDim.x;
  }
  idy+= threadIdx.y;
  
  for (int k=0; k<N; k++){
    d_C[idx*N+idy]+=Arow[k]*d_B[k*N+idy];
    idx+=threadDim.x;
  }
   
  __syncthreads();
  
}

void PRINT_MAT(int P, int M, double * matr){
  for(int j = 0; j < P; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%f ",matr[i+j*M]);
     }
    printf("\n");
  }
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
  
  for(int i=0;i<N;i++){
    h_A[i]=(double )i;
    h_B[i]=(double )i;
    h_C[i]=0.;
  }
  
  PRINT_MAT(N,N,h_A);
  PRINT_MAT(N,N,h_B);
  
  cudaMemcpy( d_A, h_A, matsize, cudaMemcpyHostToDevice );
  cudaMemcpy( d_B, h_B, matsize, cudaMemcpyHostToDevice );
  cudaMemcpy( d_C, h_C, matsize, cudaMemcpyHostToDevice );

  dim3 blockDim(BK_SIZE, BK_SIZE);
  dim3 gridDim(N/BK_SIZE, N/BK_SIZE);
  matmult<<< gridDim, blockDim >>>( d_A, d_B, d_C);
  cudaMemcpy( h_C, d_C, matsize, cudaMemcpyDeviceToHost );
  
  PRINT_MAT(N,N,h_C);
  
  free(h_A);
  free(h_B);
  free(h_C);
  
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  
  return 0;
  
}
