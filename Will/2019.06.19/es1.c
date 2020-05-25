// Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
// Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo
// comportamento.
// Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). Fare in modo che
// termini prima il figlo e poi il nipote.
// Il programma deve mostrare che con prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipote
// viene rilevata dal nonno.

#include <sys/types.h>
#include <sys/wait.h>
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

    child=fork();
    if(child==0){

        grandchild=fork();

        if(grandchild==0){
            for(long i=0; i<1000000; i++);
        }else{
            close(pipefd[0]); 
            write(pipefd[1], grandchild, sizeof(pid_t));
            close(pipefd[1]);  
        }
        
    }else{
        
        if(wait(NULL)==child)
            printf("Child dead\n");

        close(pipefd[1]);
        read(pipefd[0],&grandchild,sizeof(pid_t));
        close(pipefd[0]);

        if(wait(NULL)==grandchild)
            printf("Grandchild dead\n");
    }
    

    return 0;
}