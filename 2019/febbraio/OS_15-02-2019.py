# Scrivere un programma python che preso in input il file /usr/include/x86_64-linux-gnu/asm/unistd_64.h 
# crei in output un file .C corretto che contenga la definizione di un array:char *syscall_name[] = {"read","write",....}
# Il vettore  syscall_name  deve far corrispondere al numero di ogni system call il suo nome come stringa

def main():

    f = open("/usr/include/x86_64-linux-gnu/asm/unistd_64.h","r")
    syscallEntry = []
    for line in f.readlines():
        words = line.split(" ")
        if len(words) > 2:
            if '__NR_' in words[1]: 
                syscallEntry.append(words[1].replace('__NR_',''))

    f.close()
    toprint = []
    toprint.append("char * syscall_name[] = {")
    for syscall in syscallEntry:
        if syscall != syscallEntry[len(syscallEntry) - 1]:
            toprint.append('"'+syscall+'", ')
        else:
            toprint.append('"'+syscall+'"')

    toprint.append("};")
    stringa =''
    stringa = stringa.join(toprint)
    f = open("./output.c", "w")
    f.write(stringa)
    f.write('\n')
    f.close()
if __name__ == "__main__":
    main()