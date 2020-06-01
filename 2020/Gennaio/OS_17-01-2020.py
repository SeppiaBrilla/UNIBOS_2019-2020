'''
Esercizio 3: Python o bash: (10  punti)
Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi 
para.py sleep 20 // ls -l // ps // sleep 3 
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
'''
import os
import sys
import threading 


def main():    
    commands = []
    single_command = ""
    for arg in sys.argv[1:]:
        if '//' in arg:
            if single_command != "":
                commands.append(single_command)
                single_command = ""
        else:
            single_command = single_command + " " + arg

    commands.append(single_command)

    for command in commands:
        t = threading.Thread(target=os.system, args=(command,))
        t.start() 


if __name__ == "__main__":
    main()