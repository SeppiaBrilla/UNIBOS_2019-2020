'''
Scrivere un programma python o uno script bash che scandisca il sottoalbero relativo alle directory passate come 
parametri (o alla directry corrente se non ci sono parametri) e fornisca in output l'elenco dei file che hanno la stessa somma MD5 
(i.e. l'output del comando md5sum).
In output ogni riga deve mostrare un elenco di pathname realtivi a file che hanno la stessa somma MD5 (che quindi sono molto molto probabilmente uguali)
'''

import hashlib
import sys
import os

to_print = {}
def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def scan(folder):
    for entry in os.scandir(folder):
        if not entry.name.startswith(".") and not entry.is_dir():
            index = md5(folder + entry.name)
            if to_print.get(index):
                to_print[index] += " " + entry.name
            else:
                to_print[index] = " " + entry.name
        if entry.is_dir() and not entry.name.startswith("."):
            scan(folder +entry.name +"/")


def main():
    path = ""
    if len(sys.argv) > 1:
        path = sys.argv[1]
    else:
        path = "./"
    scan(path)
    for x in to_print:
        print(to_print[x])

    




if __name__ == "__main__":
    main()