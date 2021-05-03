#!/usr/bin/env python3

import os, sys

with open("/usr/include/x86_64-linux-gnu/asm/unistd_64.h", "r") as f:
    data = f.read()
    s = "char *syscall_name[] = {\n"
    l = data.split("\n")
    l = l[3:len(l)-3]
    i = 0
    for line in l:
        pos = line.find("__NR_")
        pos2 = line.find(" ", pos)
        sysn = line[pos+5:pos2]
        if i < len(l)-1:
            s += f'\t"{sysn}",\n'
        else:
            s += f'\t"{sysn}"\n'
        i += 1
    s += "}"
    with open("sysvector.c", "w") as f2:
        f2.write(s)

