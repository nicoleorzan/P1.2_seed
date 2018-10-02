#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

#define N 4 //size one side of the matrix
#define MPI_TAG 10
//#define DEBUG

void PRINT_MAT(int P, int M, double * matr);
void mult_mat(double * A, double * B, double * C, int l, int P, int M);

int main(int argc, char * argv[]){

  double * A, * B, *C;
  //int N;
  int Nloc;
  int rank, size;
  
 /* if( argc < 2 ){
    fprintf( stderr, "size of matrix needed!!\n");
    exit(1);
  }
  */
  //N = atoi(argv[1]);
  A = ( double * ) malloc( N * N * sizeof( double ) );
  B = ( double * ) malloc( N * N * sizeof( double ) );
  C = ( double * ) malloc( N * N * sizeof( double ) );
  
  

/*  for(int i = 0; i < N*N; i++ ){
    if (i<N+1 ){
      A[i] = 0.;// ( rand() % 100 + 1 );
      B[i] = 3.;
    }
    else  if (i>=N+1 && i<2*N+1 ){
      A[i] = 1.;
      B[i] = 2.;
    }
    else  if (i>=2*N+1 && i<3*N+1 ){
      A[i] = 2.;
      B[i] = 1.;
    }
    else {
      A[i] = 3.;
      B[i] = 0.;
    }
    C[i] = 0.;
  }
  */
 for(int i = 0; i < N*N; i++ ){
    A[i]=(double) (rand() % 100 + 1);
    B[i]=(double) (rand() % 100 + 1);
  }  
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank==0){
  printf("printing A\n");
  PRINT_MAT(N,N,A);
  printf("printing B\n");
  PRINT_MAT(N,N,B);
  printf("-----------------------------\n");
  }
  
  Nloc=N/size;  
  double * Apart, *Bpart, *Cpart;
  double buf_size_bytes = Nloc*N*sizeof(double);
  Apart = ( double * ) malloc( buf_size_bytes );
  Bpart = ( double * ) malloc( buf_size_bytes );
  Cpart = ( double * ) malloc( buf_size_bytes );

  int start=rank*N*Nloc;
  for(int i = 0; i < N*Nloc; i++ ){
    Apart[i] = A[i+start];
    Bpart[i] = B[i+start];
    Cpart[i] = 0.;
  }
  
  double * sendbuff, * recvbuff;
  sendbuff = ( double * ) malloc( Nloc * Nloc * sizeof( double ) );
  recvbuff = ( double * ) malloc( buf_size_bytes );



  
  for (int l=0; l<size; l++){ //<--------
    
    for (int j=0;j<Nloc;j++){
      for (int i=0;i<Nloc;i++){
	sendbuff[i+j*Nloc]=Bpart[l*Nloc+i+j*N];
      }
    }
    
    MPI_Allgather(sendbuff,Nloc*Nloc,MPI_DOUBLE,recvbuff,Nloc*Nloc,MPI_DOUBLE,MPI_COMM_WORLD);
 
    mult_mat(Apart,recvbuff,Cpart,l,N,Nloc);  
     
#ifdef DEBUG
      int j = 0;
      while (j < size) {
	if (rank == j) {
	  printf("rank=%d, rank*N*Nloc=%d\n",rank, rank*N*Nloc);
	  printf("sendbuff\n");
	  PRINT_MAT(Nloc,Nloc,sendbuff);
	  printf("recvbuff\n");
	  PRINT_MAT(N,Nloc,recvbuff);
	  fflush(stdout);
	}
        j++;
	MPI_Barrier(MPI_COMM_WORLD);
      }
#endif
      

  }//end l loop


  //----------------------------file writing--------------------------------
    if (rank==0){
      for(int t=0;t<N*Nloc;t++){
	C[t]=Cpart[t];
      }
      FILE * fp;
      fp = fopen( "matrix.dat", "w" );
      fwrite( C, sizeof(double), Nloc * N, fp );	
        for(int i=1; i<size; i++){
	MPI_Recv((C+i*N*Nloc), N*Nloc, MPI_DOUBLE, i, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
	fwrite( (C+i*N*Nloc), sizeof(double), Nloc * N, fp );
	if (i==size-1) {
	  printf("matrice C=A*B:\n");
	  PRINT_MAT(N,N,C);
	}
	fwrite( C, sizeof(double), Nloc * N, fp );
      }
      fclose( fp );
    }
    else{
      MPI_Send(Cpart,N*Nloc, MPI_DOUBLE, 0, MPI_TAG, MPI_COMM_WORLD);
      }

    free( sendbuff );
    free( recvbuff );
    free( Apart );
    free( Bpart );
    free( Cpart );
    //---------------------end file writing-----------------------


    MPI_Finalize();
    
    free( A );
    free( B );
    free( C );
    return 0;
    
}


void PRINT_MAT(int P, int M, double * matr){
  for(int j = 0; j < P; j++ ){
    for(int i = 0; i < M; i++ ){
      printf("%f ",matr[i+j*M]);
    }
    printf("\n");
  }
}

void mult_mat(double * A, double * B, double * C, int l, int P, int M){
    
  for (int i=0;i<M;i++){
    for (int j=0;j<M;j++){
      for (int k=0;k<P;k++){
	C[l*M+j+i*P]+=A[i*P+k]*B[k*M+j];
      }
    }
  }
}
