#include<stdio.h>
#include<assert.h>

#define N 10 //0000
#define NUM_THREADS 512

__global__ void matmult( double * d_A, double * d_B, double * d_C, int SIZE )
{
int i = threadIdx.x + (blockIdx.x * blockDim.x);
int j = threadIdx.y + (blockIdx.y * blockDim.y);

for (i=0; i<SIZE; i++){
for (j=0; j<SIZE; j++){
for (int k=0; k<SIZE; k++){
d_C[j+i*SIZE]+=d_A[i*SIZE+k]*d_B[k*SIZE+j];
}
}
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

double h_A ,h_B, h_C;
double d_A ,d_B, d_C;
size_t matsize = N * N * sizeof(double); //long integer

h_A = (double *) malloc( matsize );
h_B = (double *) malloc( matsize );
h_C = (double *) malloc( matsize );

cudaMalloc((void**), &d_A, matsize );
cudaMalloc((void**), &d_B, matsize );
cudaMalloc((void**), &d_C, matsize );

for(int i=0;i<N;i++){
h_A[i]=(double *)i;
h_B[i]=(double *)i;
h_C[i]=0.;
}

PRINT_MAT(N,N,h_A);
PRINT_MAT(N,N,h_B);

cudaMemcpy( d_A, h_A, matsize, cudaMemcpyHostToDevice );
cudaMemcpy( d_B, h_B, matsize, cudaMemcpyHostToDevice );
cudaMemcpy( d_C, h_C, matsize, cudaMemcpyHostToDevice );

matmult<<< ((N*N)+NUM_THREADS)/NUM_THREADS , NUM_THREADS >>>( d_A, d_B, d_C, N )
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