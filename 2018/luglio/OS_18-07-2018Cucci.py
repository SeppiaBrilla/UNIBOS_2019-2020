'''
Esercizio 3: Python: (10  punti):
Scrivere una shell minimale in Python usando la subprocess.run con parametro shell=False.
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input (^D).
'''
import subprocess
import sys

def main():
    while(True):
        line = sys.stdin.readline()    
        if line:
            line = line.split()
            subprocess.run(line, shell=False)    
        else:                         
            sys.exit(0)

if __name__ == "__main__":
    main()