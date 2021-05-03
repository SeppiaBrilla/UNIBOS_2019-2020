#!/usr/bin/env python3

import os, sys, grp, stat

if __name__ == "__main__":
    path = sys.argv[1]
    group = sys.argv[2]
    gid = grp.getgrnam(group)[2]

    for f in os.listdir(path):
        pathname = os.path.join(path,f)
        if not stat.S_ISDIR(os.stat(pathname).st_mode):
            if os.stat(pathname).st_gid == gid:
                print(f)
