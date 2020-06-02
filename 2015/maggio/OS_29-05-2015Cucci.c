/*
Esercizio 1: Linguaggio C (obbligatorio): (20 punti)
Scrivere un programma catsig che copi lo standard input nello standard output 
(come il comando cat senzaparametri, per intenderci) 
e che stampi la scritta “ho ricevuto un segnale” quando riceve un segnale SIGUSR1.
La particolarita' di questo programma e' che per la gestione dei segnali 
deve usare la chiamata di sistema signalfd (e non la signal o la sigaction)*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>

int main(int argc, char const* argv[]){
    sigset_t sigset;
    pid_t terminal, signal;
    int status, segnale;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);

    if(sigprocmask(SIG_BLOCK, &sigset, NULL) < 0){
		printf("sigprocmask\n");
		return 1;
	}
    
    segnale = signalfd(-1, &sigset, 0);
    if (segnale < 0) {
        perror ("signalfd");
        return 1;
    }

    signal = fork();
    if(signal == 0)
    {
        printf("PID: %d\n", getpid());
        while(1){
            ssize_t res;
            struct signalfd_siginfo si;

            res = read(segnale, &si, sizeof(si));
            
            if (res < 0) {
                perror ("read");
                return 1;
            }
            if (res != sizeof(si)) {
                fprintf (stderr, "Something wrong\n");
                return 1;
            }
            if(si.ssi_signo == SIGUSR1){
                printf("ho ricevuto un segnale!\n");
            }
	    }
    }
    else
    {
        char stringa[100];
        printf("Inserisci un comando!\n");
        while(1){
            scanf("%s", stringa);
            printf("%s\n", stringa);
        }

    }
    terminal = wait(&status);
    return 0;
}
