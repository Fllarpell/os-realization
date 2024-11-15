#!/bin/bash

gcc -pthread ex2.c -o ex2

if [ "$#" -ne 1 ]; then
    exit 1
fi

./ex2 "$1"
