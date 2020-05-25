'''
Rielaborando l'output del comando:
echo "#include<sys/syscall.h>" | gcc -dD -E -
scrivere un programma python o uno script bash che generi automaticamente un programma C che consenta di associare ogni syscall al suo numero e viceversa.
es: "sysnumber fork" deve restituire 57 mentre "sysnumber 72" deve avere come risposta fnctl(l'esempio si riferisce a sistemi di architettura x86_64)'''

import sys

def main():
    #print(sys.argv)
    syscallEntry = []
    for line in sys.argv:
        if '__NR_' in line: 
            syscallEntry.append(line.replace('__NR_',''))

    
    stringa = '''
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int isNumber(char *numb){
    while(*numb !=0){
        if(*numb < '0' || *numb > '9')
            return 0;
        numb++;
    }
    return 1;
}
    int main(int argc, char * argv[]){
        char * syscall_name[] = {'''

    for syscall in syscallEntry:
        if syscall != syscallEntry[len(syscallEntry) - 1]:
            stringa += str('"'+syscall+'", ')
        else:
            stringa += str('"'+syscall+'"')

    stringa += "};"

    stringa += '''
        int i;
        if(argc > 1){
            if (isNumber(argv[1])){
                int index = atoi(argv[1]);
                printf("%s \\n",syscall_name[index]);
                return 0;
            }
            else{
                for (int i = 0; i < 693; i++ ){
                    if(strcmp(argv[1], syscall_name[i])== 0){
                        printf("%d \\n", i);
                        return 0;
                    }
                }
            }
        }
        printf("errorr, syscall not found\\n");
        return 1;
    }'''
    f=open("./fuck.c", "w")
    f.write(stringa)
    f.close()
    
if __name__=="__main__":
    main()