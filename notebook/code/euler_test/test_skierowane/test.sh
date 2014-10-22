#! /bin/bash
#set -x

cp ../checker.cpp .
cp ../../header.h .
cat ../../euler.cpp | grep -v "NIESKIEROWANYCH" > euler.cpp
cat ../gen.py | grep -v "NIESKIEROWANYCH" > gen.py 
chmod +x gen.py

g++ checker.cpp -o checker -O2 -static -DCHECK || exit 1

for i in `seq 1 100`; do
    ./gen.py > gen.in || exit 1
    ./checker < gen.in > /dev/null || exit 1
done

g++ checker.cpp -o checker -O2 -static -I.. || exit 1
echo
echo BENCH
echo
./gen.py 100000 1000000 > gen.in
time ./checker < gen.in > /dev/null || exit 1

rm gen.in
