#!/bin/bash                                                                 

for k in 0 1 2 3 4 5 6; do
echo -n "" >tempi_loopO1${k}
for i in 1 2 3 4 5 6 7 8 9 10 11 12; do 
    gcc -O1 distribute_v${k}.c -lm
    ./a.out 50 50 2 >>tempi_loopO1${k}
done
done

