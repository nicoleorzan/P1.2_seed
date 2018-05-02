#include <omp.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

double cclock(){
    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

int main(){

  double tstart, ctime;
  struct timespec ts;
  tstart = TCPU_TIME;

  long n , i;
  double  w, x, sum, pi, a;

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

