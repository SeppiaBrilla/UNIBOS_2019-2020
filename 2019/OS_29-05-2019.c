/*
Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
Il thread produttore ripetutamente genera un numero causuale, lo stampa lo mette in una variabile condivisa con il consumatore e attende (ritardo casuale). 
Il thread consumatore legge dalla variabile condivisa i valori e li stampa (anche il consumatore attende per un periodo casuale prima di tentare di leggere il valore successivo)
Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione  si richiede di usare eventfd in modalità EFD_SEMAPHORE
*/

#include <errno.h>
#include <sys/eventfd.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <execs.h>

//compila con gcc -pthread -o ... ...
int *val;
unsigned int efdprod, efdcons;
uint64_t rd;

void *consumatore(void *arg)
{
    int pred;
    while (1)
    {
        if (read(efdcons, &rd, sizeof(uint64_t)) > 0)
        {
            srand(time(0));
            printf("Consumatore = %d \n", *val);
            if (pred == *val)
            {
                printf("ERRORE!");
                while (1)
                {
                    ;
                }
            }
            pred = *val;
            *val = 0;
            sleep(rand() % 5);
            printf("fine consumatore!\n\n");
            write(efdprod, &rd, sizeof(uint64_t));
        }
    }
    return NULL;
}

void *produttore(void *arg)
{
    int pred = 0;

    while (1)
    {
        if (read(efdprod, &rd, sizeof(uint64_t)) > 0)
        {
            srand(time(0));
            do
            {
                *val = 1 + rand() % 100;
            } while (*val == pred);
            printf("Val = %d\n", *val);
            sleep(rand() % 5);
            pred = *val;
            printf("fine produttore!\n\n");
            write(efdcons, &rd, sizeof(uint64_t));
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    efdcons = eventfd(0, EFD_SEMAPHORE);
    efdprod = eventfd(1, EFD_SEMAPHORE);
    pthread_t cons;
    pthread_t prod;
    val = (int *)malloc(sizeof(int));

    if (pthread_create(&prod, NULL, produttore, NULL))
        printf("errore produttore!\n");

    if (pthread_create(&cons, NULL, consumatore, NULL))
        printf("errore consumatore!\n");

    if (pthread_join(cons, NULL) && pthread_join(prod, NULL))
        printf("error joiningthread.\n");

    exit(0);
}

/*
Scrivere una shell minimale usando la libreria s2argv/execs (da scaricare da github).
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input(^D).
-lex-ecs or -leexecs
// */

//     #include <stdio.h>
//     #include <unistd.h>
//     #include <stdlib.h>
//     #include <execs.h>

// // gcc -lexecs -o ... ...
// #define BUFLEN 1024
// int main(int argc, char const *argv[])
// {
//     char buf[BUFLEN];
//     printf("type in a command and its arguments, e.g. 'ls -l'\n");
//     if (fgets(buf, BUFLEN, stdin) != NULL) {
//         char **argv=s2argv(buf);
//         execvp(argv[0], argv);
//         s2argv_free(argv);
//         printf("exec error\n");
//     }
// }