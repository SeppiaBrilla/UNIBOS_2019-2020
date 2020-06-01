'''
Esercizio 3: Python: (10  punti):
Scrivere una shell minimale in Python usando la subprocess.run con parametro shell=False.
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input (^D)
'''

import subprocess
import sys

def main():
    while(1):
        cmd = input()
        if cmd == "logout":
            return 0
        cmd = cmd.split(" ")
        cmd[0] = "/bin/" + cmd[0]
        subprocess.run(cmd, shell=False)


if __name__ == "__main__":
    main()