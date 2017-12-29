/*

  SETTIMO STEP: CREO LE NUOVE VARIABILI PART E JKS PER LAVORARE DIRETTAMENTE IN 3D, TOLGO LE VARIABILI MAS E GRID E LE RISPETTIVE FUNZIONI

 * This file is part of the exercises for the Lectures on 
 *   "Foundations of High Performance Computing"
 * given at 
 *   Master in HPC and 
 *   Master in Data Science and Scientific Computing
 * @ SISSA, ICTP and University of Trieste
 *
 *     This is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 3 of the License, or
 *     (at your option) any later version.
 *     This code is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License 
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h> //questi 3 sono per il calcolo dei tempi
#include <sys/times.h>
#include <time.h>
#include <math.h>


/*
 * The purpose of this code is to show you some incremental
 * optimization in loops, both in optimization and in algorithms.
 *
 * Conceptually, it is a loop over a number Np of particles
 * with tha aim of distributing the mass of the particles over the grid
 * with an appropriate weigth function, so that to have a resulting
 * density field instead of a particles distribution.
 *
 * The solution presented here below is correct, i.e. gives the
 * correct result, but it also is highly unefficient in several
 * aspects.
 *
 * Try to figure out how to make it far better.
 */


// =======================================================================
// type and global variables definition

// look at the lecture about timing for motivations about the following macro
#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec +	\
		   (double)ts.tv_nsec * 1e-9)

int main(int argc, char **argv)
{
  
  double           *parts, RMax;
  int              Np, Ng, i, j, k, p;
  
  
  // timing-related variables
  double          tstart, tstop, ctime;
  struct timespec ts;

  if( argc < 4 )
    {
      printf("3 arguments are requested:\n"
	     " (1) the number of particles to be used\n"
	     " (2) the number of grid points to be used\n"
	     " (3) the weight function (in the range [0..2]) to be used\n");
      return 0;
    }
    
  
  Np = atoi( *(argv + 1) );
  Ng = atoi( *(argv + 2) );
  RMax = 2;
  
  // allocate contiguous memory for particles coordinates
  parts = (double*)calloc(Np * 3, sizeof(double));

  // initialize random number generator
  //srand48(clock());   // change seed at each call
  srand48(997766);    // same seed to reproduce results

  // initialize mock coordinates, in the interval [0, 1[
  //printf("initialize coordinates..\n");

  // for the sake of simplicity, we'll assume that all particles have the same unitary mass

  

  int Np3 = Np*3;
  
  for(i = 0; i < Np3; i++)  parts[i] = drand48();
  // printf(" v0 :: "); fflush(stdout);

  double dist;
  double dummy=0;
  double RMax2 = RMax * RMax;
  double register half_size = 0.5 / Ng;
  double register Ng_inv = (double)1.0 / Ng;
  
  ctime = 0;
  tstart = TCPU_TIME;

  double *jks = (double*)calloc(Ng,sizeof(double));
   
  for(i = 0; i < Ng; i++) jks[i] = (double)i * Ng_inv + half_size;
  
  
  // loop over all particles
  for(p = 0; p < Np3; p+=3)
    // loop over all cells
    for(i = 0; i < Ng; i++){
      double register dx2  = parts[p] - jks[i]; dx2 = dx2 * dx2;
      for(j = 0; j < Ng; j++){
	double register dy2 =parts[p+1] - jks[j];
	dy2 = dx2 + dy2*dy2;
	for(k = 0; k < Ng; k++){
	  double register dz = parts[p+2] - jks[k];
	  dist = dy2 + dz*dz;
	  if(dist < RMax2) dummy +=sqrt(dist);
	}
      }
    }
  
  
  ctime += TCPU_TIME - tstart;

  printf("%f \n", ctime);

  free(parts);  
  free(jks);    
  
  return 0;
}
