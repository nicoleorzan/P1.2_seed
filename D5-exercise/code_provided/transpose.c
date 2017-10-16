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

int main( int argc, char * argv [] ) {

  double * A, * AT;
  int i, j;
  double t_start, t_end;
  int BLOCKSIZE, MATRIXDIM;

  if( argc < 2 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM].\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  MATRIXDIM=atoi(argv[1]);

  if( MATRIXDIM < 1 ){
    fprintf( stderr, "Error. Inconsistent parameters.\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  A = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  AT = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );

  for( i = 0; i < MATRIXDIM * MATRIXDIM; i++ ){
    A[i] = (double) i;
  }
  
  t_start=cclock();
  for( i = 0; i < MATRIXDIM; i++ ){
    for( j = 0; j < MATRIXDIM; j++ ){
      AT[ ( j * MATRIXDIM ) + i ] = A[ ( i * MATRIXDIM ) + j ];
    }
  }
  t_end=cclock(); 

  free( A );
  free( AT );
  
  fprintf( stdout, " Matrix transpose executed. Time Elapsed %9.4f secs\n", t_end-t_start );
  
  return 0;
}
