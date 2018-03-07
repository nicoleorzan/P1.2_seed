#include <omp.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>


#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec +  (double)ts.tv_nsec * 1e-9);

int main(){

  double tstart,ctime;
  struct timespec ts;
  tstart = TCPU_TIME;

  long n , i ;
  double  w,x,sum,pi,f,a;

  n = 1000000000;
  w = 1.0/n;
  sum = 0.0;

  //omp_set_num_threads(2); lo faccio da fuori
#pragma omp parallel for private(i,x) reduction (+:sum)
  for ( i = 1 ; i <= n ; i++ ) {
    x = w * (i - 0.5);
    sum = sum + (4.0 / (1.0 + x * x ) );
  }

  pi = w * sum ;
  printf("Value of pi: %.16g\n", pi);

  ctime += TCPU_TIME - tstart;
  printf("time %g\n",ctime);
  return 0;
}

