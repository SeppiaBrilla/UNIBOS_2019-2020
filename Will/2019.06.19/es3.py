# Scrivere un programma python o uno script bash che calcoli il numero di righe presenti in tutti i file .c,
# .h, e Makefile (o makefile).
# Prima deve stampare ogni per ogni file .c il numero di righe, poi il totale righe per tutti i file .c,
# similmente per i file .h e i makefile e alla fine il totale generale;

# e.g.
# primo.c 100
# secondo.c 150
# dir/terzo.c 120
# tot .c 370
# primo.h 10
# dir/terzo.h 24
# tot .h 34
#  Makefile 44
# dir/makefile 22
# tot Makefile 66
# tot source 470

import os
import sys

countSource = 0
countMake = 0

def main():
    scan_in_directory("./")
    print("tot Makefile "+str(countMake))
    print("tot source "+str(countSource))
    

def scan_in_directory(dir):
    for elem in os.scandir(dir):
        if elem.is_dir():
            scan_in_directory(str(dir)+str(elem.name)+"/")
        else:
            if elem.name.endswith(".c") or elem.name.endswith(".h"):
                fileCount(str(dir)+str(elem.name), False)
            if elem.name=="Makefile" or elem.name=="makefile":
                fileCount(str(dir)+str(elem.name), True)
                


def fileCount(path, ismake):
    global countMake
    global countSource
    linee=sum([1 for lines in open(path)])
    if ismake:
        countMake += linee
    else:
        countSource += linee

    print(path[2::]+" "+str(linee))


if __name__ == "__main__":
    main()