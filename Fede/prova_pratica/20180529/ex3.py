#!/usr/bin/env python3

import os, sys
import re

if __name__ == "__main__":
    path = "/proc/"
    userp = {}
    expr = re.compile("Uid:.*")
    for proc in os.listdir(path):
        if os.path.exists(path+proc+"/status"):
            with open(path+proc+"/status") as f:
                data = f.read()
                s = expr.search(data)
                s = s.group()
                l = s.split()[1:]
                for i in range(4):
                    userp.setdefault(l[i], [0,0,0,0])
                    userp[l[i]][i] += 1
    for key, val in userp.items():
        print(f"{key} {val[0]} {val[1]} {val[2]} {val[3]}")
