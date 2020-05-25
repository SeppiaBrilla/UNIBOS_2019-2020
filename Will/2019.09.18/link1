// scrivere un programma para per lanciare parallelamente comandi
// para sleep 20 // ls -l // ps // sleep 3
// deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 60

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

    commands[0]=malloc(sizeof(char *)*MAX_LEN);
    commands[0][0]=NULL;

    for(int i=1; i<argc; i++){
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
        if(fork()==0){
            printf("Executing %s\n",commands[i][0]);
            execv(commands[i][0], commands[i]);
            return 0;
        }
    }

    while(wait(&status)>0);
    printf("ded\n");

    return 0;
}