# MPI intranode
Apparentely `impi` is avaliable:
```
$ module load impi-trial/5.0.1.035 
```
Rune the benchmark:
```
 $ mpirun -np 2 /u/shared/programs/x86_64/intel/impi_5.0.1/bin64/IMB-MPI1 PingPong
```
## Latency measure
```
 $ mpirun -np 2 /u/shared/programs/x86_64/intel/impi_5.0.1/bin64/IMB-MPI1 PingPong
```
Three different runs statistics:

|bytes   | Run 1 [us]| Run 2 [us]| Run 3 [us]| Min [us]  | 
|------- | ----- |------ | ----- | ----- |
| 0      | 0.51  | 0.49  | 0.50  | 0.49  |
| 1      | 0.57  | 0.54  | 0.57  | 0.54  |
| 2      | 0.58  | 0.51  | 0.55  | 0.51  |

```
mpirun -np 2 /u/shared/programs/x86_64/intel/impi_5.0.1/bin64/IMB-MPI1 -iter 10000 PingPong
```
Three different runs statistics:

|bytes   | Run 1 [us]| Run 2 [us]| Run 3 [us]| Min [us]  |  
|-------:|------:|------:|------:|------:|
| 0      | 0.50  | 0.58  | 0.48  | 0.48  |
| 1      | 0.51  | 0.64  | 0.52  | 0.51  |
| 2      | 0.52  | 0.64  | 0.52  | 0.52  |

## Gauging Default Internode Communication Performance

```
mpirun -np 2 hwloc-bind core:0 core:7 /u/shared/programs/x86_64/intel/impi_5.0.1/bin64/IMB-MPI1 PingPong
```

```
mpirun -np 2 hwloc-bind core:0 core:13 /u/shared/programs/x86_64/intel/impi_5.0.1/bin64/IMB-MPI1 PingPong
```

