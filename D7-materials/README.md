## D7: hands-on and exercises 


###  openmp program and number of threads 

Try to compile run ans execute the simple `omp_101.c` code and understand correctly how to change the number of threads


### learn how to use hwloc/numactl commands

Test all the commands presented in the slides and be familiar with them.
You can try to modify the omp_101.c program to make it run longer and try to assign it on different threads by means of numactl/hwloc commands.


### Exercise 1: run stream benchmark to test different performance when wrongly assigned the processor

Take the stream benchmark (https://www.cs.virginia.edu/stream/)
compile it and familiarize with it.

Tasks:


1. Estimate the overall bandwidth of one node of ulysess 
2. Estimate the bandwidth of one single core of ulysess 
3. Compare the bandwith of one single core reading from memory associated to the socket against one core reading from memory associated with the other socket 
4. Do it for all threads available in one socket and make a plot of the results 

5.Summarize all the results in a short report and commit it to your github account 


###  run IMPI benchmark (ping-pong) to measure latency among MPI processes assigned on different cores 

You will run intel MPI ping-pong benchmark among to processors within the same node and you will try to estimate latency and bandwidth.

### Exercise 2: compile and run nodeperf.c program 

see readme.md file within the subdirectory 
 

### Exercise 3: run HPL benchmark using MKL multithread library


steps: 

- Get the HPL package from netlib::  wget http://www.netlib.org/benchmark/hpl/hpl-2.2.tar.gz 

- Compile the package against MKL library
      tips: take a look [here]https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor 

- check input file 

- check output file 

- run on different numbers of core increasing size 

- try to plot scalability and see if scalability is fine.. 

- try to identify the best combination (N and Nb) in term of performance

- compare with precompiled binary files provided by intel and available [here](https://software.intel.com/en-us/articles/intel-mkl-benchmarks-suite)

Write a short report in markdown and/or rst  format and put in this folder. 
