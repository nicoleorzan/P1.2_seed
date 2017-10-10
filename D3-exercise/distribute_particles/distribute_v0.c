/*
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
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>
#include <math.h>


/*
 * The purpose of this code is to show you some incremental
 * optimization in loops, both in optimization and in algorithms.
 *
 * Conceptually, it is a loop over a number Np of particles
 * with tha aim of distributing the mass of the particles iver the grid
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


typedef enum {NGP, CIC, TSC} MAS_type;

MAS_type MAS_select;
double   RMax;


// =======================================================================
// function declaration


double MAS(double);
double get_RMax(void);

int    ijk(int, int, int, int);

// =======================================================================
// code segment



// Mass ASsignment routine
// this routine returns the fraction of mass that have to be assigned
// to a cell at distance d
double MAS(double d)
{
  double distance = fabs(d);
  double result;
  
  if(MAS_select == NGP)
    {
      if (distance < 0.5) result=1.0;
      else if (distance == 0.5) result=0.5;
      else if (distance>0.5) result=0.0;
    }
  
  else if(MAS_select == CIC)
    result = ( distance < 1 ? 1.-distance: 0);

  else
    {
      if (distance < 0.5) result = (0.75 - pow(distance, 2));
      else if (distance >= 0.5 && distance < 1.5) result= ( 0.5 * pow(1.5-distance,2) );
      else if (distance >= 1.5) result=0.0;
    }
  
  return result;
}



double get_RMax(void)
{
  double result;
  
  if(MAS_select == NGP)
    result = 0.5;
  
  else if(MAS_select == CIC)
    result = 1.0;

  else
    result = 1.5;
  
  return result;

}



int ijk(int N, int i, int j, int k)
{
  int res;

  res = i * (N*N) + j * (N) + k;
  return res;
}



int main(int argc, char **argv)
{
  
  double           *x, *y, *z;
  double           *Grid;
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
    
  
  // get the number of particles to use
  Np = atoi( *(argv + 1) );
  // get the number of grid points
  Ng = atoi( *(argv + 2) );
  // get the type of weight function to use
  MAS_select = atoi( *(argv + 3) );

  RMax = get_RMax();
  
  // allocate contiguous memory for particles coordinates
  x    = (double*)calloc(Np * 3, sizeof(double));
  y    = x + Np;
  z    = y + Np;

  // allocate contiguous memory for grid cells
  Grid = (double*)calloc(Ng * Ng * Ng, sizeof(double));
    
  // initialize random number generator
  //srand48(clock());   // change seed at each call
  srand48(997766);    // same seed to reproduce results

  // initialize mock coordinates, in the interval [0, 1[
  printf("initialize coordinates..\n");
  for(i = 0; i < 3*Np; i++)
    x[i] = drand48();

  // for the sake of simplicity, we'll assume that all particles have the same unitary mass

  
  // ---------------------------------------------------
  // LOOP 0: the worst case
  // ---------------------------------------------------

  
  printf(" v0 :: "); fflush(stdout);

  double dist;
  double half_size = 0.5 / Ng;
  
  ctime = 0;
  tstart = TCPU_TIME;

  // loop over all cells
  for(i = 0; i < Ng; i++)
    for(j = 0; j < Ng; j++)
      for(k = 0; k < Ng; k++)
	{
	  // loop over all particles
	  for(p = 0; p < Np; p++)
	    {
	      dist = sqrt( pow(x[p] - (double)i/Ng + half_size, 2) +
			   pow(y[p] - (double)j/Ng + half_size, 2) +
			   pow(z[p]  - (double)k/Ng + half_size, 2) );
	      if(dist < RMax)
		Grid[ijk(Ng, i, j, k)] += MAS(dist);
	    }
	  }
  
  ctime += TCPU_TIME - tstart;
  
  printf("\t%g sec\n", ctime);

  free(Grid);
  free(x);
  
  return 0;
}
