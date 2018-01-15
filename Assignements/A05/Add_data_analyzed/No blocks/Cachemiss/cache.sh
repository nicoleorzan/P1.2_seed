#!/bin/bash                                                                 

gcc transpose.c -lm
for var in 1024 2048 4096; do
    >cachemiss${var}
    >cleanmiss${var}
    i=1
    while [ $i -le 12 ]; do   
	perf stat -e L1-dcache-load-misses ./a.out ${var} 2>>cachemiss${var}
	gawk '/L1-dcache-load-misses/ {print $1}' cachemiss${var} | sed 's/[^0-9]*//g' >> cleanmiss${var}
	>cachemiss${var}
	let i=i+1
    done
done
