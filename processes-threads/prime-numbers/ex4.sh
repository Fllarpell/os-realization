#!/bin/bash

gcc -pthread ex4.c -o ex4

for m in 1 2 4 10 100; do
    echo "Running with m = $m"
    /usr/bin/time -p ./ex4 10000000 $m >> ex4_res.txt
done
