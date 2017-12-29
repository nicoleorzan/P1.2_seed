/*
 * Copyright (C) 2001-2014 The Abdus Salam, International Centre of Theoretical Physics (ICTP)
 *
 * This file is distributed under the terms of the GNU General Public License. 
 * See http://www.gnu.org/copyleft/gpl.txt 
 *
 * The code is the solution for the exercise D2-exercise2 of the course P1.2 - Master in HPC @SISSA/ICTP
 * 
 * Example of code for Matrix transpose with dynamic allocation
 *
 * Author: Ivan Girotto
 * Revised by: G.P. Brandino and M. Atambo
 * Last update: Oct 2014
 * 
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

void printmat(int M , int N, double* matr){
  printf("printing matrix\n");
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      printf("%f ",matr[i*M+j]);
    }
    printf("\n");
  }
printf("\n");
}

int main( int argc, char * argv [] ) {

  double * A, * AT, *Atemp;
  int i, j;
  double t_start, t_end;
  int BLOCKSIZE, MATRIXDIM;

  if( argc < 2 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM].\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  MATRIXDIM=atoi(argv[1]);
  BLOCKSIZE=atoi(argv[2]);
  
  if( MATRIXDIM < 1 ){
    fprintf( stderr, "Error. Inconsistent parameters.\nProgram exit ...\n");//, argv[0]);
    exit(1);
  }

  A = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  AT = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  Atemp = (double *) malloc(BLOCKSIZE * BLOCKSIZE * sizeof( double ) );
  
  for( i = 0; i < MATRIXDIM * MATRIXDIM; i++ ){
    A[i] = (double) i;
  }

  //printmat(MATRIXDIM,MATRIXDIM,A);
  
  t_start=cclock();
  int numblock =MATRIXDIM/BLOCKSIZE;
  double Aswap;
  
  //finding point for starting
  int ioff, joff;
  for(int ib=0; ib<numblock; ib++){
    ioff=(ib)*BLOCKSIZE; 
    for(int jb=0; jb<numblock; jb++){
      joff=(jb)*BLOCKSIZE;
      for(int j=0;j<BLOCKSIZE; j++){
	for(int i=0;i<BLOCKSIZE; i++){
	  Atemp[j*BLOCKSIZE+i]=A[(j+joff)*MATRIXDIM+(i+ioff)];
	}
      }

      for(int j=0; j<BLOCKSIZE; j++){
       	for(int i=0; i<j; i++){
	  Aswap=Atemp[j*BLOCKSIZE+i];
	  Atemp[j*BLOCKSIZE+i]=Atemp[i*BLOCKSIZE+j];
	  Atemp[i*BLOCKSIZE+j]=Aswap;
	}
      }
      
      for(int j=0;j<BLOCKSIZE; j++){
	for(int i=0;i<BLOCKSIZE; i++){
	  AT[(j+joff)*MATRIXDIM+(i+ioff)]=Atemp[j*BLOCKSIZE+i];
	}
      }
    }
  }
  
  t_end=cclock(); 

  //printmat(MATRIXDIM,MATRIXDIM,AT);
  
  free( A );
  free( AT );
  free( Atemp );
  
  fprintf( stdout,"%f \n", t_end-t_start );
  // " Matrix transpose executed. Time Elapsed %9.4f secs\n"
  
  return 0;
}
