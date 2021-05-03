#!/usr/bin/env python3

import os, sys
import shutil

if __name__ == "__main__":
    dir1 = sys.argv[1]
    dir2 = sys.argv[2]
    mdir = sys.argv[3]
    
    fdic = {}
    for f in os.listdir(dir1):
        if os.path.isfile(os.path.join(dir1, f)):
                fdic.setdefault(f, [])
                fdic[f].append(os.path.join(dir1,f)) 
    for f in os.listdir(dir2):
        if os.path.isfile(os.path.join(dir2, f)):
                fdic.setdefault(f, [])
                fdic[f].append(os.path.join(dir2,f))
    for key, val in fdic.items():
        if len(val) <= 1:
           shutil.move(val[0], os.path.join(dir1, key))
        else:
            if(os.stat(val[0]).st_atime >= os.stat(val[1]).st_atime):
                    shutil.move(val[0], os.path.join(dir1, key))
            else:
                shutil.move(val[1], os.path.join(dir2, key))

        
