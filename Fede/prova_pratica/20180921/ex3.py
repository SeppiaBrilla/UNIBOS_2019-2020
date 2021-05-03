#!/usr/bin/env python3

import os, sys
import re
import codecs

if __name__ == "__main__":
    filedict = {}
    expr = re.compile("^\s*#!.*")
    path = sys.argv[1]
    for root, dirs, files in os.walk(path, topdown=True):
        for name in files:
            with codecs.open(os.path.join(root,name), "r", encoding='utf-8', errors='ignore') as f:
                data = f.read()
                m = expr.match(data)
                if m != None:
                    s = m.group()
                    filedict.setdefault(s, [])
                    filedict[s].append(os.path.join(root,name))
    for key, l in filedict.items():
        s = " ".join(l)
        print(f"{key}: {s}")




