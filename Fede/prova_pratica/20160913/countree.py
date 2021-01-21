#!/usr/bin/env python3

import os, sys

if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) >= 2 else "."
    dircount = 0
    filecount = 0

    for root, dirs, files in os.walk(path):
        for f in files:
            if not os.path.islink(os.path.join(root, f)):
                    filecount += 1
        for d in dirs:
            dircount += 1
    print(f"There are {dircount} directories and {filecount} files in the subtree.")
