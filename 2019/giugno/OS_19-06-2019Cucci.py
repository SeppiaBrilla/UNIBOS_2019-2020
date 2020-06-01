'''
Esercizio 3: Python o bash: (10  punti):
Scrivere un programma python che calcoli il numero di righe presenti in tutti i file .c,.h, e Makefile (o makefile).
Prima deve stampare ogni per ogni file .c il numero di righe, 
poi il totale righe per tutti i file .c,
similmente per i file .h e i makefile e alla fine il totale generale;
e.g.
    primo.c      100
    secondo.c    150
    dir/terzo.c  120
    tot .c       370

    primo.h       10
    dir/terzo.h   24
    tot .h        34    

    Makefile      44
    dir/makefile  22
    tot Makefile  66

    tot source   470
'''

import glob
import os
import sys

c = {}
h = {}
make = {}


def main():
    search("./")
    numC = numH = numMake = 0

    for file in c:
        print(file, end = " ")
        numC += c[file]
        print(c[file])
    print("tot C:", end = " ")
    print(numC)
    print()

    for file in h:
        print(file, end = " ")
        numH += h[file]
        print(h[file])
    print("tot H:", end = " ")
    print(numH)
    print()

    for file in make:
        print(file, end = " ")
        numMake += make[file]
        print(make[file])
    print("tot Make:", end = " ")
    print(numMake)
    print()
    print("totale:", end = " ù")
    print(numC+numH+numMake)

def search(path):

    for entry in os.scandir(path):
        if(entry.is_dir()):
            search(path+entry.name+"/")
        if ".c" in entry.name:
            c[path+entry.name] = file_len(path+entry.name)
        if ".h" in entry.name:
            h[path+entry.name] = file_len(path+entry.name)
        if "Makefile" in entry.name:
            make[path+entry.name] = file_len(path+entry.name)
        if "makefile" in entry.name:
            make[path+entry.name] = file_len(path+entry.name)

def file_len(fname):
    with open(fname, "r") as f:
        for i, l in enumerate(f):
            pass
    return i + 1

if __name__ == "__main__":
    main()