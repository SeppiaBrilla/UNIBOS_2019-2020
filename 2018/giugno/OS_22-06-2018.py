'''Scrivere una shell minimale in Python usando la subprocess.run con parametro shell=False.
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input (^D).'''



import subprocess


def main():
    while 1:
        args = input()
        args = args.split(" ")
        args[0] = "/bin/" + args[0]
        subprocess.run(args, shell = False)




if __name__ == "__main__":
    main()