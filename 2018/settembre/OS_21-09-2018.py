'''
Scrivere un programma python o uno script bash che trovi in un sottoalbero tutti i file che hanno come primi caratteri '#!'
e produca una tabella che elenchi tutti i pathname dei file trovati catalogando insieme i file che hanno la stessa prima riga di testo.
es:
#!/bin/bash: first.sh myscript
# #!/usr/bin/env python: prog.py'''

import glob
import os
import sys

files = {}

def main():
    search_in_directory("./")

    for first_line in files:
        #first_line = first_line.rstrip("\n")
        if len(files[first_line])>=1:
            print(first_line+":", end=" ")
            for prt in files[first_line]:
                print(prt, end=" ")
        print()

def search_in_directory(dir):
    for entry in os.scandir(dir):
        if not (entry.is_dir()):
        #    search_in_directory(dir+entry.name+"/")
        #else:
            with open(entry) as f:
                first_line = f.readline()
                #first_line.encode('utf-8').strip()
                if "#!" in first_line:
                    if not first_line in files:
                        files[first_line] = []

                    files[first_line].append(entry.name)

if __name__ == "__main__":
    main()