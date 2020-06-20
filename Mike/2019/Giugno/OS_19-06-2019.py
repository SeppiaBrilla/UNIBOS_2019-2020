'''
Esercizio 3: Python o bash: (10  punti):
Scrivere un programma python o uno script bash che calcoli il numero di righe presenti in tutti i file .c,.h, e Makefile (o makefile).
Prima deve stampare ogni per ogni file .c il numero di righe, poi il totale righe per tutti i file .c,
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

import sys
import os

filesC = {}
filesH = {}
filesM = {}
def main():
    searchInDir(sys.argv[1])
    totC = totH = totM = tot = 0

    for cfile in filesC:
        print(cfile + "     ", end = " ")
        print(filesC[cfile])
        totC += filesC[cfile]
    print("totale .c       ", totC)
    print()
    for hfile in filesH:
        print(hfile + "     ", end = " ")
        print(filesH[hfile])
        totH += filesH[hfile]
    print("totale .h      ", totH)
    print()
    for Mfile in filesM:
        print(Mfile + "     ", end = " ")
        print(filesM[Mfile])
        totM += filesM[Mfile]
    print("totale .m      ", totM)
    tot = totC + totH + totM
    print(tot)
    print()

def searchInDir(path):
    for entry in os.scandir(path):
        if(entry.is_dir()):
            searchInDir(path+entry.name+"/")
        if(entry.name.endswith('.c')):
            filesC[entry.name] = file_len(entry.name)  

        if(entry.name.endswith('.h')):
            filesH[entry.name] = file_len(entry.name)   
        if "makefile" in entry.name or "Makefile" in entry.name:
            filesM[entry.name] = file_len(entry.name)     

def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1

if __name__ == "__main__":
    main()