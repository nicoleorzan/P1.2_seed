#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>
#include <math.h>


#define DEFAULT_REPETITIONS 10

#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec +	\
		   (double)ts.tv_nsec * 1e-9)

int main(int argc, char **argv)
{
  
  double           *x, *y, *z, dist;
  double           *Grid, half_size, Rmax;
  int              Np, Ng, Iter, cc, i, j, k, p;
  
  
  // timing-related variables
  double          tstart, tstop, ctime;
  struct timespec ts;

  Np = atoi( *(argv + 1) );
  Ng = atoi( *(argv + 2) );
  
  if( argc == 4 )
    Iter = atoi( *(argv + 2) );
  else
    Iter = DEFAULT_REPETITIONS;

  // allocate contiguous memory for particles coordinates
  x    = (double*)calloc(Np * 4, sizeof(double));
  y    = x + Np;
  z    = y + Np;

  // allocate contiguous memory for grid's cells
  // Grid = (double*)calloc(Ng * Ng * Ng, sizeof(double));
  half_size = 0.5 / Ng;
  Rmax = 0.2;
  
  // initialize random number generator
  //srand48(clock());   // change seed at each call
  srand48(997766);    // same seed to reproduce results

  // initialize mock coordinates
  printf("initialize coordinates..\n");
  for(i = 0; i < 3*Np; i++)
    x[i] = drand48();



  
  // ---------------------------------------------------
  // LOOP 0: the worst case
  printf("LOOP 0 :: "); fflush(stdout);

  ctime = 0;
  double dummy = 0;

  //for(cc = 0; cc < Iter; cc++)
  //  {
  tstart = TCPU_TIME;

  for(p = 0; p < Np; p++)
    for(i = 0; i < Ng; i++)
      for(j = 0; j < Ng; j++)
	for(k = 0; k < Ng; k++)
	  {
	    dist = sqrt( pow(x[p] - (double)i/Ng + half_size, 2) +
			 pow(y[p] - (double)j/Ng + half_size, 2) +
			 pow(z[p]  - (double)k/Ng + half_size, 2) );
	    if(dist < Rmax)
	      dummy += dist;
	  }
  
  ctime += TCPU_TIME - tstart;
   // }
  
  printf("\t%g sec [%g]\n", ctime / Iter, dummy / Iter );


  // ---------------------------------------------------
  // STEP 1: replace check on dist with check on dist^2
  printf("LOOP 1 :: "); fflush(stdout);
  
  double Rmax2 = Rmax * Rmax;
  dummy = 0;
  ctime = 0;
  
  tstart = TCPU_TIME;

  for(p = 0; p < Np; p++)
    for(i = 0; i < Ng; i++)
      for(j = 0; j < Ng; j++)
	for(k = 0; k < Ng; k++)
	  {
	    dist = pow(x[p] - (double)i/Ng + half_size, 2) +
	      pow(y[p] - (double)j/Ng + half_size, 2) +
	      pow(z[p]  - (double)k/Ng + half_size, 2);
	    
	    if(dist < Rmax2)
	      dummy += sqrt(dist);
	  }
  
  ctime += TCPU_TIME - tstart;
  
  printf("\t%g sec [%g]\n", ctime / Iter, dummy / Iter );

  
  // ---------------------------------------------------
  // STEP 2: avoid calls to pow() function
  printf("LOOP 2 :: "); fflush(stdout);
  
  dummy = 0;
  ctime = 0;

  tstart = TCPU_TIME;

  for(p = 0; p < Np; p++)
    for(i = 0; i < Ng; i++)
      for(j = 0; j < Ng; j++)
	for(k = 0; k < Ng; k++)
	  {
	    double dx, dy, dz;
	    dx = x[p] - (double)i/Ng + half_size; //dx2 = dx2*dx2;
	    dy = y[p] - (double)j/Ng + half_size; //dy2 = dy2*dy2;
	    dz = z[p] - (double)k/Ng + half_size; //dz2 = dz2*dz2;
	    
	    dist = dx*dx + dy*dy + dz*dz;
	    
	    if(dist < Rmax2)
	      dummy += sqrt(dist);
	  }
  
  ctime += TCPU_TIME - tstart;
  
  printf("\t%g sec [%g]\n", ctime / Iter, dummy / Iter );


  // ---------------------------------------------------
  // STEP 3: avoid use of division
  printf("LOOP 3 :: "); fflush(stdout);
  
  double Ng_inv = (double)1.0 / Ng;

  dummy = 0;
  ctime = 0;

  tstart = TCPU_TIME;

  for(p = 0; p < Np; p++)
    for(i = 0; i < Ng; i++)
      for(j = 0; j < Ng; j++)
	for(k = 0; k < Ng; k++)
	  {
	    double dx2, dy2, dz2;
	    dx2 = x[p] - (double)i * Ng_inv + half_size; dx2 = dx2*dx2;
	    dy2 = y[p] - (double)j * Ng_inv + half_size; dy2 = dy2*dy2;
	    dz2 = z[p] - (double)k * Ng_inv + half_size; dz2 = dz2*dz2;
	    
	    dist = dx2 + dy2 + dz2;
	    
	    if(dist < Rmax2)
	      dummy += sqrt(dist);
	  }
  
  ctime += TCPU_TIME - tstart;
  
  printf("\t%g sec [%g]\n", ctime / Iter, dummy / Iter );

  
  // ---------------------------------------------------
  // STEP 4: avoid the avoidable
  printf("LOOP 4 :: "); fflush(stdout);
  
  tstart = TCPU_TIME;

  dummy = 0;
  ctime = 0;
 
  for(p = 0; p < Np; p++)
    for(i = 0; i < Ng; i++)
      {
	double dx2 = x[p] - (double)i * Ng_inv + half_size; dx2 = dx2*dx2;
      
	for(j = 0; j < Ng; j++)
	  {
	    double dy2 = y[p] - (double)j * Ng_inv + half_size; dy2 = dy2*dy2;
	    double dist2_xy = dx2 + dy2;
	    
	    for(k = 0; k < Ng; k++)
	      {
		double dz2;
		dz2 = z[p] - (double)k * Ng_inv + half_size; dz2 = dz2*dz2;
		
		dist = dist2_xy + dz2;
		
		if(dist < Rmax2)
		  dummy += sqrt(dist);
	      }
	  }
      }
	    
  ctime += TCPU_TIME - tstart;
  
  printf("\t%g sec [%g]\n", ctime / Iter, dummy / Iter );


  // free(Grid);
  free(x);
  
  return 0;
}
