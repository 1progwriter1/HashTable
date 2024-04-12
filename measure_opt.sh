#!/bin/sh

file=$1
col_tests=$2

for i in $(seq 1 "$col_tests" ); do
    ./a.out $file
done