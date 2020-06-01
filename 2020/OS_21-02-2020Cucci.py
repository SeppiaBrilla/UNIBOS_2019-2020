'''
Esercizio 3: Python o bash: (10  punti)
Scrivere un programma python che produca il listato del contenuto di una directory in ordine di suffisso.
'''

import sys
import os

def main(): 
    sortedlist = sorted([x[::-1] for x in os.listdir(sys.argv[1])])
    print([x[::-1] for x in sortedlist])

if __name__ == "__main__":
    main()