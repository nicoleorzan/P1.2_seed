# Introduction to Computer Architecture for HPC


## Stefano Cozzini / Ivan Girotto /Luca Tornatore

## OUTLINE

This repository contains the  materials/programs/assignements and workspaces for the
course **Foundation on HPC**, a course in common among MHPC and DSSC


## References&Books

#### Introduction to High Performance Computing for Scientists and Engineers
by Georg Hager and Gerhard Wellein
Paperback: 356 pages
Publication date  July 2, 2010
Editors (Chapman & Hall/CRC Computational Science)

#### Introduction to High-Performance Scientific Computing,by Victor Eijkhout
The source and pdf of the book (as well as lecture slides) can be found in this repository:
https://bitbucket.org/VictorEijkhout/hpc-book-and-course
10.5281/zenodo.49897

#### Optimizing HPC Applications with Intel Cluster Tools 
Paperback – October 15, 2014
by Alexander Supalov  (Author), Andrey Semin  (Author), Michael Klemm  (Author), & 1 more
ISBN-13: 978-1430264965  ISBN-10: 1430264969  Edition: 1st

#### High Performance Parallelism Pearls, 1st Edition
Multicore and Many-core Programming Approaches
by Reinders   &    Jeffers  
Morgan Kaufmann, Print Book ISBN :9780128021187


### Part 1: foundation on HPC  (S.C/L.T.)

- Monday October 2:
  - lecture one: [introduction to HPC] (part 1)
  - lecture two: [introduction to HPC] (part 2)
  - tutorial: using a HPC platform 
  - exercise session: [compute weak/strong scalability]  (mandatory for MHPC students)
- Friday October 6: 
  - lecture one: [modern CPU for HPC] (S.C.)
  - lecture two: [the road to exascale] (L.T)
  - exercise session: [compute weak/strong scalability] (mandatory for MHPC students)
- Monday October 9:
  - lecture one: [introduction to optimization techniques] (L.T.)
  - lecture two: [more on optimization techniques] (L.T.)
  - lecture three: [code timing] (L.T)
  - exercise session (mandatory for MHPC students)
- Wednesday October 11:
   - tutorial: again on optimization 
- Friday October 13: 
  - tutorial: [basic debugging&profiling]
  - tutorial: some more optimization techniques  
  - exercise session (mandatory for MHPC students)
- Monday October 16:
  - lecture one: [Memory hierarchy] 
  - lecture two: [memory optimization]
  - tutorial: run mountain tool. 
  - exercise session (mandatory for MHPC students) 
- Friday October 20: 
  - tutorial:   [profiling with valgrind and perf]      
  - exercise session (mandatory for MHPC students)
- Monday October 23:
  - lecture one: [multicore/multicpu platform] 
  - tutorial :   tools/methods to exploit multicore/multhithread architectures 
  - tutorial:  multicore/multithreaded  libraries 
  - exercise session (mandatory for MHPC students)
- Friday October 27: 
  - lecture one: [introduction to benchmarking] 
  - tutorial: tools for benchmarking : HPL /stream/ MPI benchmarks 
  - exercise session (mandatory for MHPC students)  
- Monday October 30:
  - lecture one: review issues and problems on assignements 
  - lecture two : final recap part one 
  - exercise session (mandatory for MHPC students)

### Assignement first part: 
 - A01: [compute weak/strong scalability] Due time: Monday 9 october midnight 
 - A02: [loop_optimization]  Due time: Monday 16 october 
 - A03: [distribute_particle] Due time: Thursday 19 october 
 - A04: [Download-a-code-and-then-profile-it-by-means-of-gprof]: Monday 23
 - A05: [Transpose a matrix] Due time Wednesday 25
 - A06: [Stream] Due time: Friday 27
 - A07: [nodeperf] Due time: November 5 (optional) midnight
 - A08: [latency_with_MPI] Due time: Monday 30 October midnight
 - A09: [HPL with MKL] Due time: November 5 midnight 
 - A10: [precompiled HPL] Due time: November 5 midnight 
 - A11: [compile_and_run HPCG] Due time: November 5 midnight 


### Part 2: parallel programming (I.G.)

- Monday November 6: 
  - lecture one: Parallel Thinking
  - lecture two : Parallel Programming with MPI (part 1)
  - tutorial: Basic Examples of Parallel Programming with MPI
  - lecture three: MPI Communications 
  - lecture four: Parallel Programming with MPI (part 2)
  - tutorial: Basic Examples of Parallel Programming 
  - exercise session (mandatory for MHPC students)
  
  ASSIGNMENT x DSSC: today assignment is the implementation of the PI approximation using MPI. 
  The exercise was presented in class and schematically described on [today slides1]. 
  The serial code is included in the hands-on folder.  

- Wednesday November 8 (for MHPC students only): 
  - lecture one: Strategies of Parallelization
  - exercise session (mandatory for MHPC students)

- Friday November 10 : 
  - lecture one: Parallel Programming with OpenMP (part 1)
  - tutorial: Basic Examples of Parallel Programming with OpenMP
  - lecture two (mandatory for MHPC students): Parallel Programming with OpenMP (part 2)
  - exercise session (mandatory for MHPC students)

  ASSIGNMENT x DSSC: today assignment is the implementation of the PI approximation using OpenMP. 
  The exercise was presented in class and schematically described on [today slides2]. 
  Provide the scaling curve of the multi-threaded version of the code on 1, 2, 4, 8, 16, 20 Threads performed on a Ulisse's compute node.  
  
- Monday November 12:
  - Parallelization of a simple problem 
  - Advanced Parallelization of a simple problem (mandatory for MHPC students)

ASSIGNMENT x DSSC: today assignment is the implementation of the Parallel Distributed MatMul as presented in class.
The Exercise is divided in 5 main points: 1) Distribute the Matrix, 2) Initialize the Distributed Matrix, 3) At every time step use MPI_Allgather to send at all processes a block of column of B, 4) Repeat point 3 for all blocks of column of B and 5) Sequential Print of the Matrix C with all processes sending data to P0 (example given in class and reference sent by e-mail). 
  
- Wednesday November 15 (for MHPC students only):
  - More exercises on MPI and OpenMP programming
  
- Friday November 17:
  - lecture one: Parallel Programming with CUDA (part 1)
  - tutorial: Basic Examples of Parallel Programming with CUDA
  - exercise session (mandatory for MHPC students)
  
ASSIGNMENT x DSSC: today assignment is the implementation of a naive version of Parallel Transpose of a NxN matrix in CUDA. 
  

- Monday November 20: 
  - lecture one: Parallel Programming with CUDA (part 2)
  - exercise session
  - lecture one: Parallel Programming with CUDA (part 3, mandatory for MHPC students)
  - exercise session (mandatory for MHPC students)

- Wednesday November 22 (S.C., L.T.): 
  - Advanced Topics  

- Friday November 24 (S.C., L.T.)
  - Benchmarking MPI applications

- Monday November 27 : 
  - lecture one: Introduction to Hybrid Programming
  - tutorial: Basic Examples of Hybrid Programming
  - advanced exercise session (mandatory for MHPC students)
  
- Wednesday November 29: (for MHPC students only)
  - Parallel Programming: How To (for MHPC students only)

- Friday December 1 (for MHPC students only):
  - Mid-term exam
  
### Part 3: advanced topics

- Monday Decemeber 4: 
  - advanced topic 1
  - exercise session (mandatory for MHPC students)
  
- Wednesday December 6:
  - advanced topic 2 

- Monday Decemeber 11: 
  - More on parallel programming 
  
- Wednesday December 13:
  - More on parallel programing  

- Friday  December 15:
  - final written exam: multiple choice test (MHPC only)

[introduction to HPC]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture1.pdf
[compute weak/strong scalability]: https://github.com/sissa/P1.2_seed/tree/master/D1-hands-on#part-2-compute-strong-and-weak-scalability-of-an-hpc-application
[modern CPU for HPC]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture2.pdf
[the road to exascale]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture2b.pdf
[introduction to optimization techniques]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture3.pdf
[more on optimization techniques]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture3b.pdf
[code timing]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture3c.pdf 
[basic debugging&profiling]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture4.pdf
[Memory hierarchy]:  https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture5.pdf
[memory optimization]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture5.pdf
[profiling with valgrind and perf]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture6.pdf
[multicore/multicpu platform]:https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture7.pdf
[introduction to benchmarking]: https://github.com/sissa/P1.2_seed/blob/master/lectures/MHPC-FHPC-lecture8.pdf
[Download-a-code-and-then-profile-it-by-means-of-gprof]: https://github.com/sissa/P1.2_seed/tree/master/D3-exercise#exercise-2--download-a-code-and-then-profile-it-by-means-of-gprof
[loop_optimization]: https://github.com/sissa/P1.2_seed/tree/master/D4-hands-on#part-1
[distribute_particle]: https://github.com/sissa/P1.2_seed/tree/master/D4-hands-on#part-2-distribute-particle-code 
[Transpose a matrix]: https://github.com/sissa/P1.2_seed/tree/master/D5-exercise#matrix-transpose-and-fast-transpose
[Stream]: https://github.com/sissa/P1.2_seed/tree/master/D7-materials#exercise-1-run-stream-benchmark-to-test-different-performance-when-wrongly-assigned-the-processor
[nodeperf]: https://github.com/sissa/P1.2_seed/tree/master/D7-materials/nodeperf#exercise-2-compile-and-run-nodeperfc-program
[latency_with_MPI]: https://github.com/sissa/P1.2_seed/blob/master/D7-materials/README.md#run-impi-benchmark-ping-pong-to-measure-latency-among-mpi-processes-assigned-on-different-cores
[HPL with MKL]: https://github.com/sissa/P1.2_seed/blob/master/D7-materials/README.md#exercise-3-run-hpl-benchmark-using-mkl-multithread-library 
[precompiled HPL]: https://github.com/sissa/P1.2_seed/blob/master/D8-materials/README.md#exercise-4-running--hpl-on--c3hpc
[compile_and_run HPCG]: https://github.com/sissa/P1.2_seed/tree/master/D8-materials#exercise-3--get-hpcg-benchmark-and-compile-it
[today slides1]:  https://github.com/sissa/P1.2_seed/blob/master/lectures/ParallelProgramming/Day2-MHPC-3.pdf
[today slides2]:  https://github.com/sissa/P1.2_seed/blob/master/lectures/ParallelProgramming/Day3-MHPC-1.pdf

### Preparation 

New material will be uploaded frequently,

Remember to set a second remote

'''
  git remote add P1.2_seed https://github.com/sissa/P1.2_seed.git
'''
or

'''
  git remote add P1.2_seed git@github.com:sissa/P1.2_seed.git
'''
and to

'''
  git pull P1.2_seed master 
'''

in the morning.


