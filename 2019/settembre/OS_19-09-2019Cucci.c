/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Scrivere un programma para per lanciare parallelamente comandi:
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

int main(int argc, char const *argv[])
{
    pid_t wpid;
    char commands[10][50], *comando[50], *riga;
    int j = 0, x = 0, status, current = 0, maxcommands;

    if (!(maxcommands = atoi(argv[1])))
    {
        printf("error");
        return 1;
    }

    if (argc < 2)
    {
        printf("Error\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
        strcpy(commands[i], "");

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "//") == 0)
            j++;
        else
        {
            strcat(commands[j], argv[i]);
            strcat(commands[j], " ");
        }
    }

    pid_t children[j];

    for (int i = 0; i <= j; i++)
    {
        if (current >= maxcommands)
        {
            wait(&status);
            current--;
        }

        current++;
        strcpy(riga, "");
        x = 0;
        strcpy(comando, "");
        comando[x] = strtok(commands[i], " ");

        while (comando[x] != NULL)
        {
            x++;
            comando[x] = strtok(NULL, " ");
        }

        strcat(riga, "/bin/");
        strcat(riga, comando[0]);

        children[i] = fork();
        if (children[i] == 0)
        {
            execv(riga, comando);
            return 0;
        }
    }

    while (wpid = wait(&status) > 0)
        ;
    return 0;
}