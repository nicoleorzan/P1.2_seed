#!/bin/bash

module load openmpi
gcc stream.c -o stream.x
for k in {1..10}; do #num di threads usati dal codice
    echo "k=" ${k}
    >${k}
    for i in {1..10}; do # num di volte
        OMP_NUM_THREADS=${k} numactl --cpunodebind 0 --membind 0 ./stream.x | grep "Triad:" | awk '{print $2}'>>${k}
	
    done
done
