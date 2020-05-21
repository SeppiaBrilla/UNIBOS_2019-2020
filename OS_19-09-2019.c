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


int main(int argc, char const *argv[])
{
    char commands[200][200];    
    if (argc < 2)
    {
        printf("Error\n");
        return 1;
    }
    int j = 0;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "//"))
        {
            j++;
        }
        else
        {
            strcat(commands[j], argv[i]);
            strcat(commands[j], " ");
        }
    }
    id_t children[j];

    for(int i = 0; i < j; i++)
    {
        children[i] = fork();
        if(children[i] == 0)
        {
            printf("%d %d %s \n",i,j, commands[i]);
        }
    }
    return 0;
}
