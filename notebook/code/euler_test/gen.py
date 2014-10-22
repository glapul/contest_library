#! /usr/bin/python
import random
import sys

#uwaga - moze wyprodukowac m+1 krawedzi
if len(sys.argv)>1:
    n = int(sys.argv[1])
    m = int(sys.argv[2])
else:
    n = random.randint(2,1000)
    m = random.randint(1, 10*n)

edges = []
def randvertex():
    return random.randint(1,n)

v = randvertex()
START = v
while len(edges)<m or v!=START:
    u = randvertex()
    while u==v:
        u = randvertex()

    if len(edges)+1>=m and v!=START: #end the cycle
        u = START

    edges.append((v,u))
    v = u

print n, len(edges)
random.shuffle(edges)
for u,v in edges:
    if random.randint(0,1)==1: u,v = v,u #DLA NIESKIEROWANYCH
    print u,v
