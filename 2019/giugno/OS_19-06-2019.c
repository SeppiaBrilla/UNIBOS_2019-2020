/*
Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo comportamento.
Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). Fare in modo chetermini prima il figlo e poi il nipote.
Il programma deve mostrare che con  prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipoteviene rilevata dal nonno.
*/


#include <sys/prctl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){

    int pidgrandad = getpid();
    int pidad;
    int pidchild;
    int go=0;
    int status;
    char name[25];

    printf("nonno %d\n",getpid());
    strcpy(name,"nonno");
    prctl(PR_SET_NAME,name);
    prctl(PR_SET_CHILD_SUBREAPER, pidgrandad);
    pidad = fork();
    if(!pidad){
        printf("enter father %d\n",getpid());
        strcpy(name,"padre");
        prctl(PR_SET_NAME,name);
        pidchild = fork();
        if(! pidchild){
            strcpy(name,"nipote");
            prctl(PR_SET_NAME,name);
            printf("entering child %d\n",getpid());
            sleep(100);
            printf("exit child\n");
            exit(1);
        }
        sleep(100);
        printf("exit father\n");
        exit(1);
    }
    
    int wpid;
    waitpid(pidad,&status,NULL);
    printf("father dead\n");
    wpid = wait(&status);
    printf("child dead %d\n",wpid);


    return 0;
}