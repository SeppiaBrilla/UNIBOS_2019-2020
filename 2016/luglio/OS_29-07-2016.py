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



if __name__ == "__main__":
    main()