# Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comaendi separati da // e aspettare la terminazione di tutti

import os
import sys
import threading

def main():

    sys.argv.remove(sys.argv[0])
    commands = str.split(" ".join(sys.argv), sep='//')

    try:
        for elem in commands:
            x = threading.Thread(target=execute, args=(elem,))
            x.start()
    except:
        print("Error: unable to start thread")


def execute(command):
    print("Running "+str(command))
    os.system(command)
    print(str(command)+" executed")

if __name__ == "__main__":
    main()