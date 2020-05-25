'''Scrivere un programma python o uno script bash che calcoli il numero di righe presenti in tutti i file .c,.h, e Makefile (o makefile).
Prima deve stampare ogni per ogni file .c il numero di righe, poi il totale righe per tutti i file .c,similmente per i file .h e i makefile e alla fine il totale generale;
e.g.
    primo.c      100
    secondo.c    150
    dir/terzo.c  120
    tot .c       370
    primo.h       10
    dir/terzo.h   24
    tot .h        34
    Makefile      44
    dir/makefile  22
    tot Makefile  66
    tot source   470
'''
import glob
import os 

c = {}
h = {}
make = {}

def Get_line(filename):
    count = 0
    with open(filename, 'r') as f:
        for line in f:
            count += 1
    return count

def search_in_directory(dir):
    for entry in os.scandir(dir):
        if(entry.is_dir()):
            search_in_directory(dir+entry.name+"/")
        else:
            filename, extension = os.path.splitext(entry.name)
            if extension == ".c":
                c[dir + entry.name] = Get_line(dir + entry.name)

            elif extension == ".h":
                h[dir + entry.name] = Get_line(dir + entry.name)

            elif filename == "Makefile" or filename == "makefile":
                make[dir + entry.name] = Get_line(dir + entry.name)
                




def main():
    ctot = htot = maketot = 0
    
    search_in_directory("./")
    for key in c:
        ctot += int(c[key])
        print(key, "    ", c[key])
    print("\ntot .c=    ", ctot, "\n")

    for key in h:
        htot += int(h[key])
        print(key, "    ", h[key])
    print("\ntot .h=    ", htot, "\n")

    for key in make:
        maketot += int(make[key])
        print(key, "    ", make[key])
    print("\ntot .make=    ", maketot, "\n")

    print("\n\ntot source =    ", maketot + ctot + htot)


if __name__=="__main__":
    main()