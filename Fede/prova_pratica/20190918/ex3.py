#!/usr/bin/env python3

import os
import sys
from stat import *

fileinodes = {}

def dirwalk(rootdir):
    for root, dirs, files in os.walk(rootdir):
        for name in files:
             inode = os.lstat(os.path.join(root,name)).st_ino
             if inode in fileinodes:
                 fileinodes.get(inode).append(os.path.join(root,name))
             else:
                fileinodes[inode] = [os.path.join(root,name)]
                
if __name__ == "__main__":
    rootdir = sys.argv[1]
    dirwalk(rootdir)

    for key, val in fileinodes.items():
        if len(val) >= 2:
            print(" ".join(val))

