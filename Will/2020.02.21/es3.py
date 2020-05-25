# Scrivere un programma python o uno script bash che produca il listato del contenuto di una directory
# in ordine di suffisso

import os
import sys

# def main():
#     sortedlist = sorted([x[::-1] for x in os.listdir(sys.argv[1])])
#     print(*[x[::-1] for x in sortedlist], sep=os.linesep)

def main():
    files = os.listdir(sys.argv[1])
    #def func(x): return os.path.splitext(x)[::-1]
    func = lambda x: os.path.splitext(x)[::-1]
    files.sort(key = func)
    print(*files, sep=os.linesep)


if __name__ == "__main__":
    main()