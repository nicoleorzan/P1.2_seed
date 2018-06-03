# Compile and run nodeperf.c program

In this part I compiled nodeperf program using. I used nodeperf to benchmark the Cosilt cluster.
To ran nodeperf I loaded the following modules:
```
module load gnu/4.8.3
module load openmpi/1.10.2/gnu/4.8.3
module load mkl/intel
```

I compiled with the following command line:
```
$ mpicc -fopenmp -O3 -g nodeperf.c  -m64 -I${MKLROOT}/include -o nodeperf.x -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
```
Then I ran with the same two commands as above.

I got the following output:
```
----------------------------------------
Begin PBS Prologue Sun Feb 25 09:59:53 CET 2018
Job ID:           168082.master
Username:         norzan
Group:            DSSC17
Nodes:            b15 
Processors:       24
End PBS Prologue Sun Feb 25 09:59:53 CET 2018
----------------------------------------
No multi-threaded MPI detected (Hybrid may or may not work)

The time/date of the run...  at Sun Feb 25 09:59:54 2018

This driver was compiled with:
	-DITER=4 -DLINUX -DNOACCUR -DPREC=double 
Malloc done.  Used 1846080096 bytes
(0 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22230.664 b15
(1 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23001.081 b15
(2 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22161.380 b15
(3 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22986.397 b15
(4 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22234.891 b15
(5 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23022.093 b15
(6 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22244.861 b15
(7 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23020.059 b15
(8 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22237.189 b15
(9 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23013.722 b15
(10 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22238.036 b15
(11 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22934.947 b15
(12 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22231.528 b15
(13 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23004.714 b15
(14 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22241.679 b15
(15 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23010.607 b15
(16 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22242.441 b15
(17 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22968.708 b15
(18 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22232.921 b15
(19 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22995.530 b15
(20 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22233.860 b15
(21 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 23013.322 b15
(22 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22158.391 b15
(23 of 24): NN lda=15000 ldb= 192 ldc=15000 0 0 0 22987.775 b15
```
We can immediately notice the written phrase ```No multi-threaded MPI detected (Hybrid may or may not work)```.
Here we are reaching 23020.059 Mflops, which is the 4.44% of the theoretical peak performance. May be that this way nodeperf does not work because multi-threading is not working.
