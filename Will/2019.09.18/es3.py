# Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sottoalbero
# che sono link fisici fra loro:
# e.g.
# searchln mydir
# mydir/a mydir/d/b mydir/qq
# mydir/uno mydir/due
# significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, cosi' come mydir/uno
# mydir/due indicano uno stesso file (diverso dal precedente).
# Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicati
# nell'output

import os
import sys

inodeCollector = {}

def main():
    search_in_directory(sys.argv[1])
    for elem in inodeCollector:
        if len(inodeCollector[elem])>1:
            print(*inodeCollector[elem], sep=" ")

def search_in_directory(dir):
    for elem in os.scandir(dir):
        if elem.is_dir():
            search_in_directory(str(dir)+"/"+elem.name)
        else:
            if not str(elem.inode()) in inodeCollector:
                inodeCollector[str(elem.inode())] = []

            inodeCollector[str(elem.inode())].append(str(dir)+"/"+elem.name)

if __name__ == "__main__":
    main()