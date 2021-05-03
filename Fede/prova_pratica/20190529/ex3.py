#!/usr/bin/env python3

import os, sys
import subprocess

if __name__ == "__main__":
    sysc = sys.argv[1]
    data = subprocess.run(["gcc", "-dD", "-E", "-"], input="#include<sys/syscall.h>".encode(), stdout=subprocess.PIPE)
    data = data.stdout.decode('ascii')
    pos = data.find("__NR_"+sysc)
    pos2 = data.find("\n", pos)
    pos3 = data.find(" ", pos, pos2)
    print(data[pos3+1:pos2])
