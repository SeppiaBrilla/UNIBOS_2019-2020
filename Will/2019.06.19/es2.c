// Tramite l'opzione PR_SET_NAME sempre di prctl fare in modo che con il comando "ps -Leo pid,comm"
// i nomi dei tre rpocessi creati dall'esercizio 1 compaiano con nome "nonno","figlio" e "nipote".

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[]){

    int pipefd[2];
    volatile long i = 0;
    char buff;
    pipe(pipefd);
    pid_t child, grandchild;
    char nome[16];

    prctl(PR_SET_CHILD_SUBREAPER);

    child=fork();
    if(child==0){

        grandchild=fork();

        if(grandchild==0){
            for(long i=0; i<10000000; i++);
            strcpy(nome,"nipote");
            prctl(PR_SET_NAME, nome);
        }else{
            strcpy(nome,"figlio");
            prctl(PR_SET_NAME, nome);
            close(pipefd[0]); 
            write(pipefd[1], &grandchild, sizeof(pid_t));
            close(pipefd[1]);  
        }
        
    }else{
        strcpy(nome,"nonno");
        prctl(PR_SET_NAME, nome);
        if(wait(NULL)==child)
            printf("Child dead\n");

        close(pipefd[1]);
        read(pipefd[0],&grandchild,sizeof(pid_t));
        close(pipefd[0]);

        if(wait(NULL)==grandchild)
            printf("Grandchild dead   %d\n",getpid());
    }
    

    return 0;
}