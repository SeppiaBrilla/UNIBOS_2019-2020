/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo comportamento.
Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). Fare in modo che termini prima il figlo e poi il nipote.
Il programma deve mostrare che con  prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipote viene rilevata dal nonno.

Esercizio 2: Linguaggio C: 10 punti
Tramite l'opzione PR_SET_NAME sempre di prctl fare in modo che con il comando "ps -Leo pid,comm"i nomi dei tre processi creati dall'esercizio 1 compaiano con nome "nonno","figlio" e "nipote".
*/

#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    pid_t children, grandchild, father = getpid();
    int status;
    char *name;
    prctl(PR_SET_CHILD_SUBREAPER, father);

    printf("entering Father: %d\n", getpid());
    strcpy(name, "nonno");
    prctl(PR_SET_NAME, name);
    children = fork();
    if (!children)
    {
        grandchild = fork();
        if (!grandchild)
        {
            printf("entering Grandchild: %d\n", getpid());
            strcpy(name, "nipote");
            prctl(PR_SET_NAME, name);
            sleep(20);
            exit(1);
        }
        printf("entering Child: %d\n", getpid());
        strcpy(name, "figlio");
        prctl(PR_SET_NAME, name);
        sleep(20);
        exit(1);
    }

    int wpid;
    waitpid(children, &status, NULL);
    printf("children dead\n");
    wpid = wait(&status);
    printf("Grandchild dead %d\n", wpid);

    return 0;
}