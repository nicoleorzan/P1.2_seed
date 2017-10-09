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


#define RCPU_TIME (getrusage(RUSAGE_SELF,&ruse), ruse.ru_utime.tv_sec + \
		   + 1e-6 * ruse.ru_utime.tv_usec)

#define TCPU_TIME (clock_gettime( id, &ts ), (double)ts.tv_sec +	\
		   (double)ts.tv_nsec * 1e-9)

#define CLOCK_DIFF(BEG, END) ((double)(END - BEG) / CLOCKS_PER_SEC)

int main(int argc, char **argv)
{
  
  double        *x, *y, *z, *dist;
  int           N, i, j, k;

  double          rstart, rstop;
  double          tstart, tstop;
  clock_t         begin, end;
  struct rusage   ruse;
  struct timespec ts;
  clockid_t       id;

  id = CLOCK_PROCESS_CPUTIME_ID;

  N = atoi( *(argv + 1) );

  // allocate contiguous memory
  x    = (double*)calloc(N * 4, sizeof(double));
  y    = x + N;
  z    = y + N;
  dist = z + N;

  // initialize random number generator
  srand48(clock());

  // initialize mock coordinates
  printf("initialize coordinates..\n");
  for(i = 0; i < 3*N; i++)
    x[i] = drand48();

  // loop 1
  printf("first loop\n");

#define REPETITIONS 100  
  int test_counter;
  double ctime, rtime, ttime;


  ctime = 0;
  for(test_counter = 0; test_counter < REPETITIONS; test_counter++)
    {
      begin = clock();
      for(i = 0; i < N; i++)
	for(j = 0; j < N; j++)
	  for(k = 0; k < N; k++)
	    {
	      dist[i] = pow(x[i], 2) + pow(y[j], 2) + pow(z[k], 2);
	    }
      end = clock();
      ctime += CLOCK_DIFF(begin, end);
    }

  rtime = 0;
  for(test_counter = 0; test_counter < REPETITIONS; test_counter++)
    {
      rstart = RCPU_TIME;
      
      for(i = 0; i < N; i++)
	for(j = 0; j < N; j++)
	  for(k = 0; k < N; k++)
	    {
	      dist[i] = pow(x[i], 2) + pow(y[j], 2) + pow(z[k], 2);
	    }
      rtime += RCPU_TIME - rstart;
    }

  ttime = 0;
  for(test_counter = 0; test_counter < REPETITIONS; test_counter++)
    {
      tstart = TCPU_TIME;
      
      for(i = 0; i < N; i++)
	for(j = 0; j < N; j++)
	  for(k = 0; k < N; k++)
	    {
	      dist[i] = pow(x[i], 2) + pow(y[j], 2) + pow(z[k], 2);
	    }
      ttime += TCPU_TIME - tstart;
    }
  
  printf("\tLOOP 1:: clock(): %g - getrusage: %g - gettime : %g\n",
	 ctime / REPETITIONS,
	 rtime / REPETITIONS,
	 ttime / REPETITIONS );

  free(x);
  
  return 0;
}
