/*
Esercizio 1: 
Linguaggio C (obbligatorio) 20 punti
Fare un programma di confronto parallelo di file.

    pcmp file1 file2

non stampa nulla se i due file sono uguali altrimenti stampa "file1 file2 differ". 
pcmp deve creare due processi figli;

mentre un processo controlla la prima meta’ del file, l'altro deve controllare l’altra meta’.
Se un dei due processi figli trova una differenza, termina immediatamente segnalandolo al padre con opportuno valore di ritorno. 
In questo caso il padre deve terminare l'altro processo.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int filecmp(char f1[], char f2[], int i, int f)
{
    for (int k = i; k < f && k < 1000; k++)
    {
        if (f1[k] != f2[k])
        {
            printf("file diversi!\n");
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Beep Boop, your file is wrong\n");
        return -1;
    }

    FILE *f1;
    FILE *f2;

    if ((f1 = fopen(argv[1], "r")) == NULL)
    {
        printf("errore puttana madonna!\n");
        return 1;
    }
    if ((f2 = fopen(argv[2], "r")) == NULL)
    {
        printf("errore puttana madonna!\n");
        return 1;
    }

    char c1[1000], c2[1000];
    int i = 0;

    do
    {
        c1[i] = fgetc(f1);
        c2[i] = fgetc(f2);
        i++;
    } while (c1[i - 1] != EOF && c2[i - 1] != EOF);
    i--;

    fclose(f1);
    fclose(f2);

    id_t child_a, child_b;
    pid_t wpida, wpidb;
    int status = 0;
    int *r1, *r2;

    child_a = fork();

    if (child_a == 0)
        filecmp(c1, c2, 0, i / 2);
    else
    {
        child_b = fork();

        if (child_b == 0){
            filecmp(c1, c2, i / 2, i);
        }
        else
        {
            while ((wpida = waitpid(child_a, &status, 0)) > 0 && (wpidb = waitpid(child_a, &status, 0)) > 0)
                ;
            
            printf("%d %d",wpida,wpidb);
            kill(child_a, SIGKILL);
            kill(child_b, SIGKILL);
        }
    }

    return 0;
}