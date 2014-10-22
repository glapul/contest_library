#! /bin/bash
#set -x

g++ checker.cpp -o checker -O2 -static -DCHECK -I.. || exit 1

for i in `seq 1 100`; do
    ./gen.py > gen.in || exit 1
    ./checker < gen.in > /dev/null || exit 1
done
./checker < izol.in > /dev/null || exit 1

g++ checker.cpp -o checker -O2 -static -I.. || exit 1
echo
echo BENCH
echo
./gen.py 100000 1000000 > gen.in
time ./checker < gen.in > /dev/null || exit 1

rm gen.in
