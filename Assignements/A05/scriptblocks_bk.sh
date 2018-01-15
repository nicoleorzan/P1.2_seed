#!/bin/bash                                                                     

gcc transpose_block.c -lm
for dim in 1024 2048 4096; do
>out_block_2_${dim}
dimblock=1
while [ $dimblock -le 1024 ]; do
    echo $dimblock
    echo $dimblock>>out_block_2_${dim}
    i=0
    while [ $i -le 12 ]; do
	./a.out ${dim} ${dimblock} >>out_block_2_${dim}
	let i=i+1
    done
    echo "" >>out_block_2_${dim}
    let dimblock=dimblock*2
done
done
