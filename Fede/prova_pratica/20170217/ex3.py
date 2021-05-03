#!/usr/bin/env python3

import os, sys

if __name__ == "__main__":
    path = sys.argv[1]
    filedict = {}
    nosuff = []

    for f in os.listdir(path):
        if os.path.isfile(os.path.join(path,f)):
            pos = f.find(".")
            if pos > 0:
                suff = f[pos:]
                filedict.setdefault(suff, [])
                filedict[suff].append(f)
            else:
                nosuff.append(f)
    for key, val in filedict.items():
        print(f"{key}: {' '.join(val)}")
    print(" ".join(nosuff))
