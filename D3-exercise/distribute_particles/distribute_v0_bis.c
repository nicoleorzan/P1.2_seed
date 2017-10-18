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

typedef unsigned long long int ULL;

MAS_type MAS_select;
double   RMax;

// [change]
// this variables are now global
double   size, cell_size, half_size;


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
    result = cell_size;
  
  else if(MAS_select == CIC)
    result = cell_size;

  else
    result = 1.5 * cell_size;
  
  return result;
}



int ijk(int N, int i, int j, int k)
{
  return i * N*N + j * N  + k;
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

  size = 1.0;
  cell_size = 1.0 / Ng;
  half_size = cell_size / 2.0;
  
  RMax = get_RMax();

  // allocate contiguous memory for grid cells
  // [change]
  // you should always check whether the memory allocation has succeeded
  if( (Grid = (double*)calloc(Ng * Ng * Ng, sizeof(double))) == NULL )
    {
      printf("unable to allocate %lu bytes of memory, I have to say good bye it's time to die\n", Ng * Ng * Ng * sizeof(double));
      exit(1);
    }

  // allocate contiguous memory for particles coordinates
  // [change]
  // you should always check whether the memory allocation has succeeded
  if( (x    = (double*)calloc(Np * 3, sizeof(double))) == NULL)
    {
      printf("unable to allocate %lu bytes of memory, I have to say good bye it's time to die\n", Np * 3 * sizeof(double));
      free(Grid);
      exit(1);
    }
  y    = x + Np;
  z    = y + Np;


    
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

  printf("\nstart vb run:: \n"
	 "\t MAS type  : %d\n"
	 "\t     RMax  : %g\n"
	 "\t     Grid  : %-3d^3\n"
	 "\t particles : %-4d\n\n",
	 
	 MAS_select, RMax, Ng, Np ); fflush(stdout);

#ifdef DEBUG
  // [change]
  // debug variables
  int dbg_assignments, *dbg_done;
  dbg_assignments = 0;
  dbg_done        = (int*)calloc(Np, sizeof(int));
#endif

  ctime = 0;
  tstart = TCPU_TIME;
  
  // loop over all cells
  for(i = 0; i < Ng; i++)
    for(j = 0; j < Ng; j++)
      for(k = 0; k < Ng; k++)
	for(p = 0; p < Np; p++)
	  {
	    // loop over all particles
	    double dist = sqrt( pow(x[p] - ((double)i/Ng + half_size), 2) +
				pow(y[p] - ((double)j/Ng + half_size), 2) +
				pow(z[p] - ((double)k/Ng + half_size), 2) );
	    
	    if(dist < RMax)
	      {
		Grid[ijk(Ng, i, j, k)] += MAS(dist / cell_size);
#ifdef DEBUG		      		  
		/* printf("p (%g %g %g) %d visits cell %d %d %d" */
		/*        " (dist is %g | %g | %g | %g)\n", */
		/*        x[p], y[p], z[p], p, i, j, k, dist, */
		/*        x[p] - ((double)i/Ng + half_size), */
		/*        y[p] - ((double)j/Ng + half_size), */
		/*        z[p] - ((double)k/Ng + half_size) ); */
		// [change]
		// keep track about the particles assigned and about the total # of assignments
		dbg_assignments++;
		dbg_done[p]++;
#endif
	      }
	  }
  
  ctime += TCPU_TIME - tstart;

#ifdef DEBUG
  // [change]
  for(j = 0, i = 0; i < Np; i++)
    if(dbg_done[i] == 0)
      j++;
  
  if(j > 0)
    printf("\nWARNING:: %d particles have not be assigned to any cell\n", j);

  printf("\nrun took %g seconds, %d assignments done\n", ctime, dbg_assignments);
  free(dbg_done);
#else
  printf("\nrun took %g seconds\n", ctime);
#endif


  // [change]
  // write the grid by column in ascii format, with small significant digits so
  // that to not much sensitive to errors in summation
  // ... verification...
  FILE *file;
  int   N;

  file = fopen("grid_v0_rd.dat", "w");
  
  N = Ng *Ng;
  for(i = 0; i < N; i++)
    {
      k = i*Ng;
      for(j = 0; j< Ng; j++)
	fprintf(file, "%9.6g ", Grid[k + i]);
      fprintf(file, "\n");
    }
  
  fclose(file);
  
  free(Grid);  
  free(x);

  return 0;
}
