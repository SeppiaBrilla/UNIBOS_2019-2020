/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo comportamento.
Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). 
Fare in modo che termini prima il figlio e poi il nipote.
Il programma deve mostrare che con  prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipote viene rilevata dal nonno.
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int main(int argc, char const* argv[]){
    pid_t father, son, grandchild = getpid();
    int status;
    char *nome;
    prctl(PR_SET_CHILD_SUBREAPER, 0, 0, 0, 0);
    strcpy(nome,"nonno");
    prctl(PR_SET_NAME,nome, 0, 0 ,0);
    printf("entering Father: %d\n", getpid());
    son = fork();
    if(!son){
        printf("Entrato nel figlio con pid = %d\n", getpid());
        strcpy(nome,"figlio");
        prctl(PR_SET_NAME,nome, 0, 0 ,0);
        grandchild = fork();
        if(!grandchild){
            printf("Entrato nel nipote con pid = %d\n", getpid());
            strcpy(nome,"nipote");
            prctl(PR_SET_NAME,nome, 0, 0 ,0);
            sleep(10);
            exit(1);
        }
        sleep(10);
        exit(1);    
    }
    int wpid;
    waitpid(son, &status, 0);
    printf("Children dead\n");
    wpid = wait(&status);
    printf("Grandchild dead %d\n", wpid);
    return 0;
}