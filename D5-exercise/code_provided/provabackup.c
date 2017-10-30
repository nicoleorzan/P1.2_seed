/*
Questo programma implementa la trasposizione di una matrice a blocchi, ma ora funziona sol con blocchi di dimensione sottomultipla della dimensione della matrice principale.


*/
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>


double cclock()
  /* Returns elepsed seconds past from the last call to timer rest */
{

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}


int main(int argc,char* argv[]){
  double * A, * AT,  *Atemp;
  int i, j;
  int BLOCKSIZE, MATRIXDIM;
  double t_start, t_end;

  

  if( argc < 3 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM].\nProgram exit ...", argv[0]);
    exit(1);
  }
   MATRIXDIM=atoi(argv[1]);
  BLOCKSIZE=atoi(argv[2]);
  
  A = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  AT = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  Atemp = ( double * ) malloc( BLOCKSIZE * BLOCKSIZE * sizeof( double ) );
  
  //MATRIXDIM=atoi(argv[1]);
  //BLOCKSIZE=atoi(argv[2]);

  for( i = 0; i < MATRIXDIM * MATRIXDIM; i++ ){
    A[i] = (double) i;
    AT[i]= 0.;
    //printf("%f  ", A[i]);
    if (i==MATRIXDIM) printf("\n");
  }
  //printf("\n --------------------- \n");
  
  int nblock=MATRIXDIM/BLOCKSIZE;
  //printf("nblock: %d \n",nblock);
  int h=0,l=0,f=0;

  t_start=cclock();
  for(int k = 0; k < nblock*nblock; k++ ){
    // printf("k: %d \n",k);
    //printf("h: %d \n",h);
  if (h<nblock) {
    for( i = 0; i < BLOCKSIZE; i++ ){
      for( j = 0; j < BLOCKSIZE; j++ ){
	Atemp[j*BLOCKSIZE+i]=A[MATRIXDIM*i+j+BLOCKSIZE*k+l];
	AT[MATRIXDIM*j+i+k*MATRIXDIM*(BLOCKSIZE)+f]=Atemp[j*BLOCKSIZE+i];
	}
      }
    }
    h++;
    if (h==nblock){
      l+=MATRIXDIM*(BLOCKSIZE-1);
      f+=BLOCKSIZE-MATRIXDIM*BLOCKSIZE*nblock;
      h=0;
    }



    
    /*  for( i = 0; i < BLOCKSIZE; i++ ){
      for( j = 0; j < BLOCKSIZE; j++ ){
	printf("%f ", Atemp[i*BLOCKSIZE+j]);
      }
      }
      printf("\n ///// \n");*/
 }
  t_end=cclock();

 
 int y=0;
 for( i = 0; i < MATRIXDIM; i++ ){
   for( j = 0; j < MATRIXDIM; j++ ){
     //printf("%f ", AT[i*MATRIXDIM+j]);
     y++;
     if (y==MATRIXDIM){
       //printf("\n");
       y=0;
     }
   }
 }
 //printf("\n");

  
  free( A );
  free( AT );
  free(Atemp);

  fprintf( stdout, "%f \n" ,t_end-t_start);
/*" Matrix transpose executed. Time Elapsed %9.4f secs",*/
  
  return 0;
}
