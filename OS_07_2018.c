/*Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Lo scopo di questo esercizio è di scrivere un programma che conti quanti segnali di tipo SIGUSR1 e quanti di tipoSIGUSR2 riceve. 
Ogni volta che riceve un segnale di tipo SIGUSR1 deve aumentare un contatore di 1, ogni volta che riceve SIGUSR2 deve decrementare di 1 il contatore. 
A ogni variazione del contatore il programma stampa il valore. Questo programma deve essere realizzato usando la system call signalfd.

Esercizio 2: Linguaggio C: 10 punti
Estendere la soluzione dell'esercizio 1: Modificare il programma dell'esercizio 1 
per fare in modo che alla partenza scriva il proprio pid nel file /tmp/countpid. 
Scrivere poi un secondo programma che lanci il comando con argomenti
passato come parametro, prima di eseguire il comando deve mandare SIGUSR1 
al programma dell'esercizio 1, al termine deve mandare SIGUSR2.
e.g.
    count sleep 20... 
spedisce SIGUSR1, esegue sleep 20, manda SIGUSR2. 
In questo modo il programma dell'esercizio 1 dovrebbe
contare quanti comandi lanciati con il programma count sono in corso di esecuzione

*/

#include <signal.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

static int contatore = 0;

int main(int argc, char const *argv[])
{
    sigset_t mask;
    ssize_t c;
    struct signalfd_siginfo inserimento;
    int error, sfd;

    FILE *f = fopen("./countpid", "w");
    fprintf(f, "%d \n", getpid());
    fclose(f);

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    if(sigprocmask(SIG_BLOCK, &mask, NULL) < 0){
		perror ("sigprocmask");
		return 1;
	}
    
    sfd = signalfd(-1, &mask, 0);
    if (sfd < 0) {
		perror ("signalfd");
		return 1;
	}


    for (;;)
    {
        c = read(&mask, &inserimento, sizeof(struct signalfd_siginfo));
        if (c != sizeof(struct signalfd_siginfo)){
            perror("read");
            return 1;
        }

        if (inserimento.ssi_signo == SIGUSR1){
            contatore++;
            break;
        }
        if (inserimento.ssi_signo == SIGUSR2){  
            contatore--;
            break;
        }

    }
    printf("%d \n", contatore);
    return 0;
}
