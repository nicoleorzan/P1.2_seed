#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#define STACKSMASHint 2*1024*1024    // the number of integers needed to smash a stack limit of 8MB
#

void func1(unsigned int S)
/*
 * array here is dynamically allocated, and as such
 * memory is allocated into the heap, not into the
 * stack.
 * that's why it does not lead to a seg fault when
 * called even if S*sizeof(int) is larger than the
 * stack size
 */
{
  int *array;
  unsigned int i;

  array = (int*)malloc(S * sizeof(int));
  for(i = 0; i < S; i++)
	array[i] = i;
  free(array);
  
  printf("allocation of %zd bytes on the heap done\n", S * sizeof(int)); fflush(stdout);
  return;	
}


void func2(void)
/*
 * usually the linux stack limit is set at 8192KB, so this
 * routine will cause a seg fault when called.
 * try to set a different stack limit through
 *   ulimit -s <limit>
 * or to decrease the dimension of array
 */
{
  int volatile array[STACKSMASHint]; // try to get 8192K on the stack
  int i;

  for(i = 0; i < 2*1024*104 + 10; i++)
	array[i] = i;
  
  printf("allocation of %zd bytes on stack has done\n", STACKSMASHint * sizeof(int)); fflush(stdout);
  return;
}


int main(int argc, char **argv)
{
  unsigned int  S;
  struct rlimit stack_limits;
  
  getrlimit(RLIMIT_STACK, &stack_limits);
      

  // get the memory to be allocated in MB
  if(argc > 1)
    
    S = atoi(*(argv+1));
  
  else
    {
      S = stack_limits.rlim_cur;
      
      printf("you did not give a memory amount to be allocated, "
	     "I'll use the current soft stack limit of %u\n(hard limit is set to %d)\n",
	     S, (int)stack_limits.rlim_max);
    }

  // convert it in how many integers are required to fill the requested memory
  S /= sizeof(int);

  // call func1
  func1(S);


  if((int)stack_limits.rlim_max < 0)
    {
      const struct rlimit mystack_limits = {STACKSMASHint * sizeof(int) + stack_limits.rlim_cur, stack_limits.rlim_max};
      /* mystack_limits = stack_limits; */
      /* mystack_limits.rlim_cur = (STACKSMASHint  + 512) * sizeof(int) / 1024;  */
      setrlimit(RLIMIT_STACK, &mystack_limits);
    }
  
  // call func2
  func2();

  setrlimit(RLIMIT_STACK, &stack_limits);
  return 0;
}
