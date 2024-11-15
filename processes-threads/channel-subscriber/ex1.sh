#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Error related with number of subscribers"
    exit 1
fi

n=$1

mkdir -p /tmp/ex1

for ((i = 1; i <= n; i++)); do
    mkfifo /tmp/ex1/s$i
done

./publisher $n &

for ((i = 1; i <= n; i++)); do
    ./subscriber $i &
done
