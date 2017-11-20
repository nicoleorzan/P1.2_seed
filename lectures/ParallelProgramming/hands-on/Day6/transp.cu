#include<stdio.h>
#include<assert.h>

#define N 10 //0000
#define NUM_THREADS 512

__global__ void transpose( double * d_A, double * d_AT )
{
int idx = threadIdx.x + (blockIdx.x * blockDim.x);
int idy = threadIdx.y + (blockIdx.y * blockDim.y);

if (idx<N){
if (idy<N){
d_AT[idx + idy*N] = d_A[ind*N + idy];
}
}

void PRINT_MAT(int N, int M, double * matr){
  for(int j = 0; j < N; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%f ",matr[i+j*M]);
    }
    printf("\n");
  }
}

}

int main(){

double h_A, h_AT;
double d_A, d_AT;
size_t matsize = N * N * sizeof(double); //long integer

h_A = (double *) malloc( matsize );
h_AT = (double *) malloc( matsize );

cudaMalloc((void**), &d_A, matsize );
cudaMalloc((void**), &d_AT, matsize );

for(int i=0;i<N;i++){
h_A[i]=(double *)i;
h_AT[i]=0.;
}

PRINT_MAT(N,N,h_A);

cudaMemcpy( d_A, h_A, matsize, cudaMemcpyHostToDevice );
cudaMemcpy( d_AT, h_AT, matsize, cudaMemcpyHostToDevice );

transpose<<< ((N*N)+NUM_THREADS)/NUM_THREAD , NUM_THREADS >>>( d_A , d_AT )
cudaMemcpy( h_AT, d_AT, matsize, cudaMemcpyDeviceToHost );

PRINT_MAT(N,N,h_AT);

free(h_A);
free(h_AT);

cudaFree(d_A);
cudaFree(d_AT);

return 0;

}
