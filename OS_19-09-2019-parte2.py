'''
Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sottoalbero che sono link fisici fra loro:
e.g.
searchln mydir
mydir/a mydir/d/b mydir/qq
mydir/uno mydir/due
significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, cosi' come mydir/unomydir/due indicano uno stesso file (diverso dal precedente).
Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicatinell'output.
'''
import glob
import os 

files = {}

def main():
    search_in_directory("./")
    
    for inode in files:
        if len(files[inode])>1:
            for prt in files[inode]:
                print(prt, end= " ")
            print()

def search_in_directory(dir):
    for entry in os.scandir(dir):
        if(entry.is_dir()):
            search_in_directory(dir+entry.name+"/")
        else:
            if not entry.inode() in files:
                files[entry.inode()] = []
                
            files[entry.inode()].append(dir+entry.name)



if __name__ == "__main__":
    main()