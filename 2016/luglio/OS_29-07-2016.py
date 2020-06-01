'''
Esercizio 3: Script bash o Python: (10  punti):
Scrivere la funzione groupdir in python.
void printgroupdir(const char *dirp, const char *group);
che deve scandire la directory con pathname dirp e stampare  tutti i file (non le directory) che appartengano al gruppo passato come secondo parametro.
'''
import sys
import os
import grp

def main():
    search(sys.argv[1])


def search(path):
    for entry in os.scandir(path):
        if not entry.is_dir():
            stat_info = os.stat('/'+path)
            group = grp.getgrgid(stat_info.st_gid)[0]
            if(group == sys.argv[2]):
                print(entry.name, end = " ")
                print(group)
'''
Scrivere un programma python (o uno script bash) che dato come parametro il pathname di una directory ponga ino utput il numero dei file e delle directory contenute 
nel sottoalbero senza contare I file simbolici

import os
import sys


def search_in_dir(directory):
    value = 0
    for entry in os.scandir(directory):
        if not entry.is_dir():
            if not os.path.islink(directory+"/"+entry.name):
                value +=1
        else:
            value += search_in_dir(directory+"/"+entry.name)

    return value

def main():
    if len(sys.argv) ==2:
        print(search_in_dir(sys.argv[1]))
    else:
        print("errore")



if __name__ == "__main__":
    main()
'''