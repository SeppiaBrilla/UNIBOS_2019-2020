'''
Scrivere uno script che faccia il merge dei contenuti due directory:merge a b c
Tutti i file (non le directory) esistenti in a e in b devono essere spostati in c. 
Nel caso due file con lo stesso nome compaiano sia in a sia in b, il file spostato in c deve essere quello piu' recentementente modificato, 
l’altro deve rimanere nella directory di origine.
'''

import os 
import shutil
import sys


def move(source_A, source_B, destination):
    file_from_a = []
    for f in os.listdir(source_A):
        file_from_a.append(f)
    
    file_from_b = []
    for f in os.listdir(source_B):
        file_from_b.append(f)
    
    for f in file_from_a:
        if f in file_from_b:
            if(os.stat(source_A+"/"+f).st_mtime > os.stat(source_B+"/"+f).st_mtime):
                shutil.move(source_A+"/"+f, destination+"/"+f)
        else:
            shutil.move(source_A+"/"+f, destination+"/"+f)

    for f in file_from_b:
        if f in file_from_a:
            if(os.stat(source_B+"/"+f).st_mtime > os.stat(source_A+"/"+f).st_mtime):
                shutil.move(source_B+"/"+f, destination+"/"+f)
        else:
            shutil.move(source_B+"/"+f, destination+"/"+f)

    


def main():
    if len(sys.argv) < 4:
        print("too few arguments")
        return 1

    move(sys.argv[1], sys.argv[2], sys.argv[3])
    print("all file moved")



if __name__=="__main__":
    main()