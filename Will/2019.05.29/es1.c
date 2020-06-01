// Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
// Il thread produttore ripetutamente genera un numero causuale, lo stampa lo mette in una variabile
// condivisa con il consumatore e attende (ritardo casuale). Il thread consumatore legge dalla variabile
// condivisa i valori e li stampa (anche il consumatore attende per un periodo casuale prima di tentare di
// leggere il valore successivo)
// Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione si richiede di
// usare eventfd in modalità EFD_SEMAPHORE.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/eventfd.h>

struct arg_struct{
    int sem[2];
    uint64_t rd;
    int val;
};

void *produttore(void *argument){
    srand(time(NULL));
    struct arg_struct *arguments = argument;
    while (1)
    {
        if(read(arguments->sem[0], &arguments->rd, sizeof(uint64_t))>0){

            arguments->val=rand()%100 + 1;
            printf("Numero prodotto: %d\n",arguments->val);

            write(arguments->sem[1], &arguments->rd, sizeof(uint64_t));
        }
        sleep((rand()%20)/10);
    }
    
}

void *consumatore(void *argument){
    srand(time(NULL));
    struct arg_struct *arguments = (struct arg_struct *)argument;
    int lettura;
    while (1)
    {    
        if(read(arguments->sem[1], &arguments->rd,sizeof(uint64_t))>0){
            
            lettura=arguments->val;
            arguments->val=0;
            printf("Numero letto: %d\n",lettura);

            write(arguments->sem[0], &arguments->rd, sizeof(uint64_t));

        }
        sleep((rand()%20)/10);
    }
    
}


int main(int argc, char * argv[]){
    pthread_t cons;
    pthread_t prod;
    struct arg_struct arguments;
    arguments.sem[0]=eventfd(1, EFD_SEMAPHORE);
    arguments.sem[1]=eventfd(0, EFD_SEMAPHORE);

    if(pthread_create(&prod, NULL, produttore, &arguments)){
        printf("Error creating producer\n");
        return 1;
    }
    if(pthread_create(&cons, NULL, consumatore, &arguments)){
        printf("Error creating consumer\n");
        return 1;
    }

    if(pthread_join(prod, NULL) && pthread_join(cons, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;

    }
    return 0;
}
