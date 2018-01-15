#!/bin/bash                                                                     

echo -n "">>cachemiss1024.txt
gcc transpose_block.c -lm
dimblock=0
while [ $dimblock -le 100 ]
do   
    perf stat -e L1-dcache-load-misses ./a.out 1024 ${dimblock} 2>>cachemiss1024.txt
    let dimblock=dimblock+1
done

