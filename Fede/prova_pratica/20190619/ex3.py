#!/usr/bin/env python3

import os, sys

def checkf(name, l):
    with open(name) as f:
        lines = sum(1 for line in f)
        l.append((name, lines))


if __name__ == "__main__":
    path = sys.argv[1]
    cfiles = []
    hfiles = []
    mfiles = []

    for root, dirs, files in os.walk(path, topdown=True):
        for name in files:
            if name.endswith(".c"):
                checkf(root+"/"+name, cfiles)
            if name.endswith(".h"):
                checkf(root+"/"+name, hfiles)
            if name == "makefile" or name == "Makefile":
                checkf(root+"/"+name, mfiles)
    
    totsum = 0
    csum = 0
    for el in cfiles:
       print(el[0] + f"\t{el[1]}")
       csum += el[1]
       totsum += el[1]
    print(f"tot .c\t{csum}")
    hsum = 0
    for el in hfiles:
        print(el[0] + f"\t{el[1]}")
        hsum += el[1]
        totsum += el[1]
    print(f"tot .h\t{hsum}")
    msum = 0
    for el in mfiles:
        print(el[0] + f"\t{el[1]}")
        msum += el[1]
        totsum += el[1]
    print(f"tot Makefile\t{msum}")
    print(f"tot source\t{totsum}")
