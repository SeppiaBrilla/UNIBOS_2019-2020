'''
Esercizio 3: Script bash o Python: (10  punti):
Lo script  o il programma devono mostrare le righe che compaiono ripetute nei file della directory corrente
Per ogni riga ripetuta devono essere mostrati: 
    il contenuto della riga, 
    il file dove compare, 
    il numero di linea del file.
Per “righe ripetute” si intendono righe di testo con lo stesso contenuto dalla prima alla ultima lettera significativa, cioe' a meno dell'indentazione iniziale (con spazi o tab).'''

import sys
import os

class fileline:
    def __init__(self):
        self.mult = 0
        self.occ = []

    def add_occ(self,occ):
        self.occ.append(occ)
        self.mult +=1
    
    def __str__(self):
        return "molteplicità =" + str(self.mult) + " in " + str(self.occ)

def main():
    all_files = []
    search_in_dir(".", all_files)
    tp = []
    for File in all_files:
        for line in File:
            if line != "": 
                n = 0
                files = []
                for f in all_files:
                    count = f.count(line)
                    if count > 0:
                        files.append(f[0]+ " ")
                        n += count
                
                if n > 1:
                    strn = line + " " + str(n) + str(files)
                    if not strn in tp:
                        tp.append(strn)
    
    print(tp)

def search_in_dir(directory, files):
    for entry in os.scandir(directory):
        if entry.is_dir():
            search_in_dir(entry.name, files)
        else:
            f = open(entry.name, "r")
            nf = []
            nf.append(entry.name)
            for line in f:
                nf.append(line.strip())

            files.append(nf)

            

if __name__ == "__main__":
    main()