#!/bin/bash

gcc -O0 transpose_block.c -lm
for dim in 1024 2048 4096 8192; do
dimblock=1
while [ $dimblock -le 1024 ]; do
    >${dim}_${dimblock}_O0
    echo $dimblock
    i=0
    while [ $i -le 12 ]; do
        ./a.out ${dim} ${dimblock} >>${dim}_${dimblock}_O0
        let i=i+1
    done
    let dimblock=dimblock*2
done
done

gcc -O1 transpose_block.c -lm
for dim in 1024 2048 4096 8192; do
dimblock=1
while [ $dimblock -le 1024 ]; do
    >${dim}_${dimblock}_O1
    echo $dimblock
    i=0
    while [ $i -le 12 ]; do
        ./a.out ${dim} ${dimblock} >>${dim}_${dimblock}_O1
        let i=i+1
    done
    let dimblock=dimblock*2
done
done

gcc -O2 transpose_block.c -lm
for dim in 1024 2048 4096 8192; do
dimblock=1
while [ $dimblock -le 1024 ]; do
    >${dim}_${dimblock}_O2
    echo $dimblock
    i=0
    while [ $i -le 12 ]; do
        ./a.out ${dim} ${dimblock} >>${dim}_${dimblock}_O2
        let i=i+1
    done
    let dimblock=dimblock*2
done
done

gcc -O3 transpose_block.c -lm
for dim in 1024 2048 4096 8192; do
dimblock=1
while [ $dimblock -le 1024 ]; do
    >${dim}_${dimblock}_O3
    echo $dimblock
    i=0
    while [ $i -le 12 ]; do
        ./a.out ${dim} ${dimblock} >>${dim}_${dimblock}_O3
        let i=i+1
    done
    let dimblock=dimblock*2
done
done

gcc -O0 transpose.c -lm
for dim in 1024 2048 4096 8192; do
i=0
while [ $i -le 12 ]; do
	./a.out ${dim} >>${dim}_O0
	let i=i+1
done

gcc -O1 transpose.c -lm
for dim in 1024 2048 4096 8192; do
i=0
while [ $i -le 12 ]; do
	./a.out ${dim} >>${dim}_O1
	let i=i+1
done

gcc -O2 transpose.c -lm
for dim in 1024 2048 4096 8192; do
i=0
while [ $i -le 12 ]; do
	./a.out ${dim} >>${dim}_O2
	let i=i+1
done

gcc -O3 transpose.c -lm
for dim in 1024 2048 4096 8192; do
i=0
while [ $i -le 12 ]; do
	./a.out ${dim} >>${dim}_O3
	let i=i+1
done


