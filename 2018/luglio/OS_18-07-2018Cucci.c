/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Lo scoopo di questo esercizio è di scrivere un programma che conti quanti segnali di tipo SIGUSR1 e quanti di tipoSIGUSR2 riceve. 
Ogni volta che riceve un segnale di tipo SIGUSR1 deve aumentare un contatore di 1, ogni volta che riceve SIGUSR2 deve decrementare di 1 il contatore. 
A ogni variazione del contatore il programma stampa il valore. Questo programma deve essere realizzato usando la system call signalfd

Estendere la soluzione dell'esercizio 1: 
Modificare il programma dell'esercizio 1 per fare in modo che alla partenza scriva il proprio pid 
nel file /tmp/countpid. 
Scrivere poi un secondo programma che lanci il comando con argomenti passato come parametro, prima di eseguire il comando deve mandare SIGUSR1 al programma dell'esercizio 1, al termine deve mandare SIGUSR2.
e.g. count sleep 20... spedisce SIGUSR1, esegue sleep 20, manda SIGUSR2. In questo modo il programma dell'esercizio 1 dovrebbecontare quanti comandi lanciati con il prgramma count sono in corso di esecuzione.
*/

#include <signal.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[]){
    int contatore = 0, sfd;
    sigset_t mask;
    struct signalfd_siginfo fdsi;
    ssize_t s;
    FILE *fp;
    char stringa[20];

    strcpy(stringa, "/tmp/countpid");
    fp = fopen(stringa, "w");
    fprintf(fp,"%d\n" ,getpid());
    fclose(fp);
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    sigprocmask(SIG_BLOCK, &mask, NULL);

    sfd = signalfd(-1, &mask, 0);
    printf("%d\n", getpid());
    while(1){
        read(sfd, &fdsi, sizeof(fdsi));
        if(fdsi.ssi_signo == SIGUSR1)
            contatore++;
        if(fdsi.ssi_signo == SIGUSR2)
            contatore--;
        printf("%d\n", contatore);
    }
    return 0;
}