#! /bin/bash
#set -x

g++ checker.cpp -o checker -O2 -static -I.. || exit 1

for i in `seq 1 5`; do
    ./gen.py 1000000 10000000 > gen.in
    time ./checker < gen.in > /dev/null || exit 1
done

rm gen.in
