/*
Esercizio 1: Linguaggio C (obbligatorio): (20 punti)
    Scrivere un programma che preso come parametro un file contenente un elenco di comandi 
    (con I relativi parametri) li attivi tutti in esecuzione concorrente e rimanga in attesa. 
    Quando il primo termina, vengono terminati (con segnale SIGTERM) tuttigli altri. 
    (consiglio: puo' essere utile usare la mia libreria s2argv-execs) 

s2argv converts a command string into an argv array for execv, execvp, execvpe. 
execs is like execv taking a string instead of an argv. 
Similarly execsp and execspe are the counterpart of execvp and execvpe, respectively, using command strings.
int execv(const char *path, char *const argv[]);

    esempio:
        ./wta commands
    il file commands contiene:
        ./ttest 40
        ./ttest 10
        ./ttest 20
    lo script ./ttest contiene:
        #!/bin/bash
        echo waiting for $1 seconds
        sleep $1
        echo done $i
    l'ouptut sara':
        waiting for 40 seconds
        waiting for 10 seconds
        waiting for 20 seconds
        done 10
    e poi basta perche' gli altri processi verranno terminati.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execs.h>

int main(int argc, char const *argv[])
{
   
    //execv(./test)
    FILE * commands = fopen(argv[1], "r");
    char * line;
    char ** command;
    size_t len = 0;

    if (commands == NULL)
        printf("suca");
    
    while(getline(&line, &len, commands) != -1){
        printf("%s", line);
        int count=0;
        char buf[40];
        while(line[count])!=' '){
            buf[count]=line[count];
            count++;
        }
        count++;
        //s2argv converts a command string into an argv array for execv, execvp, execvpe. 
        command = s2argv(line+count);
        execv(command[0],command);
    }

    fclose(commands);
    return 0;
}