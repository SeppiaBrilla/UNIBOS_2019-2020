#!/usr/bin/env/ python3

import os
import sys
import subprocess
import time

if __name__ == "__main__":
    s = " ".join(sys.argv[1:])
    cmdl = s.split("//")
    children = []
    for cmd in cmdl:
        l = cmd.split(" ")
        for el in l:
            if el == "":
                l.remove(el)
        p = subprocess.Popen(l)
        children.append(p)

    for child in children:
        child.wait()


