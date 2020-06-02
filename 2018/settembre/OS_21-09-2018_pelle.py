'''
Scrivere un programma python o uno script bash che trovi in un sottoalbero tutti i file che hanno come primicaratteri '#!' e 
produca una tabella che elenchi tutti i pathname dei file trovati catalogando insieme i file chehanno la stessa prima riga di testo.
es:
#!/bin/bash: first.sh myscript
#!/usr/bin/env python: prog.py
'''

import os 

def search_in_folder(directory,files):
    for entry in os.scandir(directory):
        
        if entry.is_dir():
            search_in_folder(directory+entry.name+"/",files)
        else:
            f = open(directory+entry.name)
            fl = str(f.readline())
            if fl.startswith("#!"):
                if fl in files:
                    files[fl] += entry.name + " " 
                else:
                    files[fl] = entry.name + " " 



def main():
    tp = {}
    search_in_folder("./",tp)
    print(tp)



if __name__ =="__main__":
    main()