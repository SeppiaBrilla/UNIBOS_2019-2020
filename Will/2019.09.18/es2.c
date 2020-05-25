// estendere para a paran che ha un parametro che indica il numero massimo di esecuzioni concorrenti:
// paran 3 sleep 20 // ls -l // ps // sleep 3
// al max esegue 3 comandi in parallelo, quindi esegue i primi 3 comandi, qundo uno fra essi termina
// ne attiva un successivo e cosi' via.

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 60
#define MAX_PROC atoi(argv[1])

void aggiungi(char * comando[], char * parola){
    int count=0;

    while(count<(MAX_LEN-1) && comando[count]!=NULL){
        printf("%s ",comando[count]);
        count++;
    }

    if(count==0){
        comando[0]=malloc(sizeof(char)*1024);
        strcpy(comando[0],"/bin/");
        strcat(comando[0],parola);
        printf("%s\n",comando[0]);
    }
    else if(count<MAX_LEN-1){
        comando[count]=parola;
        comando[count+1]=NULL;
        printf("%s\n",comando[count]);
    }
}

int main(int argc, char * argv[]){
    char ** commands[30];
    int commandindex=0;
    int status;
    int processes=0;

    commands[0]=malloc(sizeof(char *)*MAX_LEN);
    commands[0][0]=NULL;

    for(int i=2; i<argc; i++){
        if(strcmp(argv[i],"//")==0){
            commandindex++;
            commands[commandindex]=malloc(sizeof(char *)*MAX_LEN);
            commands[commandindex][0]=NULL;
        }
        else{
            aggiungi(commands[commandindex], argv[i]);
        }
        
    }

    for (int i = 0; i <= commandindex; i++){
        if(processes==MAX_PROC){
            wait(&status);
            processes--;
        }
        if(fork()==0){
            printf("Executing %s\n",commands[i][0]);
            execv(commands[i][0], commands[i]);
            return 0;
        }else{
            processes++;
            printf("%d\n",processes);
        }

    }

    while(wait(&status)>0);
    return 0;
}