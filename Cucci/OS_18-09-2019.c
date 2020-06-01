/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
scrivere un programma para per lanciare parallelamente comandi
para sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const* argv[]){
    pid_t wpid;
    char *currentcommand[20], listOfCommands[10][50], riga[120];
    int j = 0, x = 0, status, currentStatus, MaxProcess;

    if(argc < 2){
        printf("Hello\n");
        return 1;
    }

    if(MaxProcess = atoi(argv[1]) == 0){
        printf("Error!\n");
        return 1;
    }


    for(int i = 0; i< 10; i++)
        strcpy(listOfCommands[i], "");

    for(int i = 2; i < argc; i++)
    {   
        if(strcmp(argv[i], "//") != 0){
            strcat(listOfCommands[j], argv[i]);
            strcat(listOfCommands[j], " ");
        }
        else
            j++;
    }

    pid_t prc_id[j];

    for(int i = 0; i <= j; i++){
        x = 0;
        if(currentStatus >= MaxProcess){
            wait(&status);
            currentStatus--;
        }
        currentStatus++;
        currentcommand[x] = strtok(listOfCommands[i], " ");

        while (currentcommand[x] != NULL)
        {
            x++;
            currentcommand[x] = strtok(NULL, " ");
        }
        strcpy(riga, "/bin/");
        strcat(riga, currentcommand[0]);
        
        prc_id[i] = fork();
        if(prc_id[i] == 0){   
            
            execv(riga, currentcommand);
            printf("fuck\n");
            return 0;
        }
    }
    while (wpid = wait(&status) > 0)
        ;
    return 0;
}