#!/usr/bin/env python3

import os
import sys
import hashlib

if __name__ == "__main__":
    filedict = {}
    path = sys.argv[1]
    h = hashlib.md5()
    for fname in os.listdir(path):
        with open(path+fname, 'r') as f:
            data = f.read()
            data = data.encode('utf-8')
            h.update(data)
            key = h.hexdigest()
            filedict.setdefault(key, [])
            filedict[key].append(fname)
    for key, val in filedict.items():
        newname = path+"new"+val[0]
        os.link(path+val[0],newname)  
        for el in val:
            os.remove(path+el)
            
