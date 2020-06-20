'''
Esercizio 3: Python o bash: (10  punti):
Scrivere un programma python o uno script bash che faccia l'elenco dei pathname 
in un sottoalbero che sono link fisici fra loro:
e.g.
searchln mydirmy
dir/a mydir/d/b mydir/qq
mydir/uno mydir/due
significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file,
cosi' come mydir/unom ydir/due indicano uno stesso file (diverso dal precedente).
Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicati nell'output.
'''

import sys
import os

Files = {}
def main():
    searchInDir(sys.argv[1])

    for inode in Files:
        if len(Files[inode]) > 1:
            for ind in Files[inode]:
                print(ind, end= " ")
            print()

def searchInDir(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            searchInDir(path + "/" + entry.name)
        if not entry.inode() in Files:
            Files[entry.inode()] = []
        Files[entry.inode()].append(path+entry.name)

if __name__ == "__main__":
    main()

