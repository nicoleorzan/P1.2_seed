#!/bin/bash                                                                     

gcc transpose.c
for var in 1024 2048 4096; do
echo -n "" >out${var}
for i in 1 2 3 4 5 6 7 8 9 10 11 12; do
    ./a.out ${var} >>out${var}
done
done
