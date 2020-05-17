'''Esercizio 3: Python o bash: (10  punti)
Scrivere un programma python che consenta di  
lanciare parallelamente comandi:
para.py sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti'''

import threading
import sys
import os

def main():

    process = []
    commands = []
    single_command = ""
    print(sys.argv)
    for single in sys.argv:
        if single == "//" or single == "para.py":
            if single_command != "":
                commands.append(single_command)
                single_command = ""

        else:
            single_command += " " + single

    for command in commands:
        t = threading.Thread(target=  os.system, args= (command,))
        t.start()


if __name__ == "__main__":
    main()