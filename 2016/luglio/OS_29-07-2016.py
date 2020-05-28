'''
Scrivere un programma python (o uno script bash) che dato come parametro il pathname di una directory ponga ino utput il numero dei file e delle directory contenute 
nel sottoalbero senza contare I file simbolici
'''
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