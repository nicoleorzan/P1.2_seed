## D8: hands-on and exercises 


###  run IMPI benchmark (ping-pong) to measure latency among MPI processes assigned on different cores 

You will run intel MPI ping-pong benchmark among to processors within the same node and you will try to estimate latency and bandwidth.

### Exercise 2: compile and run nodeperf.c program 

see readme.md file within the subdirectory 


### Exercise 3:  get HPCG benchmark and compile it 


steps: 

- Get the HPCG package from netlib::http://www.hpcg-benchmark.org/downloads/hpcg-3.0.tar.gz   


- Compile the package against MKL library
      tips: take a look [here]https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor 

- Try to run it and check if numbers does make sense..  

### Exercise 4: Running  HPL on  C3HPC (precompiled version) 


Connect to the machine
```
ssh  your account @hpc.c3e.cosint.it 
```
Submit interactive job: 

```
qsub -I -l nodes=$NODE:ppn=24 -l walltime=6:0:0 -N $GROUP
```

Identify the right (i.e. the most efficient)  executable in  `/lustre/mhpc/eas/hpl/bin`
among the following:
```
xhpl.plasma-gnu
xhpl.openblas
xhpl.netlib
xhpl.mkl-gnu
xhpl.atlas
xhpl.plasma-mkl
```

Execute some of them on small testset and select the most performing ones:

- Load appropriate modules
- prepare a simple input file (HPL.dat) in your directory
- Run/test it on a small matrix: 

```
mpirun  -np XX  /lustre/mhpc/eas/hpl/bin/xhpl.mkl-gnu
```
Beware of threads
How to control them ? 

Check out wrap.sh  and run.sh 
Once selected the best executable identify a suitable size of your problem

N should be large enough to take ~75% of RAM..
N = sqrt ( 0.75 * Number of Nodes * Minimum memory of any node / 8 )
You can compute it via: 
http://www.advancedclustering.com/act-kb/tune-hpl-dat-file/

Test a few N and Nb to identify the most performing one..
Tip:
Write a small script and submit

Compute the ratio between theoretical peak performance and sustained hpl performance.

You should be able to identify the right combination to get at least 75% of peak performance.
Minimum acceptance test. 

