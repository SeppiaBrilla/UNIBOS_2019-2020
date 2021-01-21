#!/usr/bin/env python3

import os, sys
import re
from operator import itemgetter

if __name__ == "__main__":
    procs = {}
    l = []
    exp = re.compile("^\d*$")
    path = "/proc/"
    for proc in os.listdir(path):
        fdpath = path+proc+"/fd"
        if os.access(fdpath,os.R_OK | os.F_OK) and exp.match(proc) != None:
            procs[proc] = len(os.listdir(fdpath))

    for key, val in procs.items():
        l.append((key, val))
    l.sort(key=itemgetter(1),reverse=True)
    for el in l:
        print(f"{el[0]} {el[1]}")
