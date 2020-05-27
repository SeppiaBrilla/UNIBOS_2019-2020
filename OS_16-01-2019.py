'''
Esercizio 3: Python o bash: (10  punti):
getent passwd mostra l'intero elenco degli utenti del sistema distribuito del dipartimento in formato passwd(5).
Scrivere uno script o un programma Python che elaborando opportunamente l'output di 'getent passwd' conti gli utenti a seconda della directory dove e' posta la home: 
e.g.
/home/faculty 65
/home/students 2496
...e cosi' via. 
Il programma deve poter funzionare in sistemi che usano una diversa suddivisione delle home degli utenti 
(cioé nel programma non devono comparire costanti come /home/faculty o simili,le categorie devono venir calcolate a partire dal campo 'home' del formato).'''

import subprocess
import sys


def search(folder):
    counter = 0
    for line in sys.argv:
        if folder in line:
            searcherlist = line.split("/home/")
            searcher = folder + searcherlist[1].split(":")[0] + "/"
            search(searcher)
            counter += 1
    if counter > 0 :
        print(folder + " " + str(counter))
    

def main():
    search("/home/")

if __name__ == "__main__":
    main()