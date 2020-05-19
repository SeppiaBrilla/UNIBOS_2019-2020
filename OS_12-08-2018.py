import os
import subprocess 
import sys

def main():
    commans = []
    commans = sys.argv
    commans.pop(0)
    subprocess.run(commans, shell=False)
    exit()





if __name__ == "__main__":
    main()