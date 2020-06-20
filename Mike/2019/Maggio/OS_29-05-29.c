/*
Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
Il thread produttore ripetutamente genera un numero causuale, 
lo stampa lo mette in una variabile condivisa con il consumatore e attende (ritardo casuale). 
Il thread consumatore legge dalla variabile condivisa i valori e li stampa 
(anche il consumatore attende per un periodo casuale prima di tentare di leggere il valore successivo)
Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione si richiede di usare eventfd in modalità EFD_SEMAPHORE.*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <stdio.h>

int consumer, producer;
ssize_t fd;
uint64_t buf;
int val;

void * consumatore(void * arg){
    srand(time(0));
    int valore;
    while(1){
        read(consumer, &buf, sizeof(uint64_t));
        valore = val;
        printf("Consumatore consuma: %d\n", valore);
        sleep(rand()%5);
        if (write(producer, &buf, sizeof(buf)) == -1)
            printf("Errore\n");
    }
}

void * produttore(void * arg){
    srand(time(0));
    while(1){
        read(producer, &buf, sizeof(buf));
        val = rand()%100;
        printf("Produttore produce: %d \n", val);
        sleep(rand()%5);
        write(consumer, &buf, sizeof(buf));
    }
}

int main(int argc, char const* argv[]){

    pthread_t p_consumer, p_producer;

    consumer = eventfd(0, EFD_SEMAPHORE);
    producer = eventfd(1, EFD_SEMAPHORE);

    printf("Hello\n");
    if(pthread_create(&p_producer, 0, produttore,0 ))
        printf("Yeeted\n");
    if(pthread_create(&p_consumer, 0, consumatore,0 ))
        printf("Second\n");
    if(pthread_join(p_consumer, 0) && pthread_join(p_producer, 0))
        printf("Errore nei join\n");
    
    return 0;
}