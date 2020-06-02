'''
Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sotto albero
che sono link fisici fra loro:
e.g.
searchln mydir 
mydir/a mydir/d/b mydir/qq
mydir/uno mydir/due
significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, 
cosi' come mydir/unomydir/due indicano uno stesso file (diverso dal precedente).
Nel sottoalbero possono esserci molteplici altri file, 
se hanno un solo nome non vengono indicati nell'output
'''

import sys
import os

files= {}

def main():
    searchDirectory(sys.argv[1])

    for file in files:
        if len(files[file]) > 1:
            for stringa in files[file]:
                print(stringa , end =" ")
            print()

def searchDirectory(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            searchDirectory(path+entry.name+"/")
        if not entry.inode() in files:
            files[entry.inode()] = []
        
        files[entry.inode()].append(path+entry.name)

if __name__ == "__main__":
    main()