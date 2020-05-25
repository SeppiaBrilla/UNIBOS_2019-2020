# Scrivere un programma python o uno script bash che cerchi tutti i file con uguale contenuto in una
# directory. I file con lo stesso contenuto devono diventare link fisici a un unico file.

import sys
import os
import filecmp
import itertools

files=[]

def main():
    add_file(sys.argv[1])
    for primo, secondo in itertools.combinations(files, 2):
        if filecmp.cmp(primo,secondo):
            #files.remove(secondo)
            os.remove(secondo)
            os.link(primo,secondo)

def add_file(dir):
    for elem in os.scandir(dir):
        if elem.is_dir():
            add_file(dir+"/"+elem.name)
        else:
            files.append(dir+"/"+elem.name)


if __name__ == "__main__":
    main()