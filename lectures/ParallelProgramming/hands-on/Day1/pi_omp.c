#include <omp.h>
#include <stdio.h>

int main(){

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

  return 0;
}

