#!/bin/bash                                                                 

gcc transpose_block.c -lm
for blocks in 1 2 4 8 16 32 64 128 256 512 1024; do
    >${blocks}
    >clean${blocks}
    i=1
    while [ $i -le 12 ]; do   
	perf stat -e L1-dcache-load-misses ./a.out 4096 ${blocks} 2>>${blocks}
	gawk '/L1-dcache-load-misses/ {print $1}' ${blocks} | sed 's/[^0-9]*//g' >> clean${blocks}
	>${blocks}
	let i=i+1
    done
done
