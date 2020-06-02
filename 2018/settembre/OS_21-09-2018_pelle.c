/*
Lo scopo di questo esercizio è di scrivere un programma che usando la system call signalfd quando riceve unsegnale SIGUSR1 o SIGUSR2 scriva in un file della directory 
corrente con nume uguale al pid del processo che hainviato il segnale, il tipo di segnale ricevuto e l'ora esatta di ricezione del segnale. 
(se il file non esiste deve esserecreato).
un esempio di file risultante potrebbe essere:
$ cat 20231
USR1  Fri Sep 21 10:40:56 CEST 2018 
USR1  Fri Sep 21 10:40:58 CEST 2018 
USR2  Fri Sep 21 10:41:26 CEST 2018
*/

#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



int main(int argc, char* argv[]){

    sigset_t mask;
    int fd;
    struct signalfd_siginfo signal;
    ssize_t size;
    time_t t = time(NULL);
    struct tm tt;
    FILE *f;
    char pid[7];
    char message[50];
    


    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1){
        printf("sigprocmask\n");
        return 1;
    }

    fd = signalfd(-1, &mask, 0);
    if (fd == -1){
        printf("signalfd");
        return 1;
    }

    printf("pid = %d\n",getpid());

    while(1){
        size = read(fd, &signal, sizeof(struct signalfd_siginfo));
        t = time(NULL);
        tt = *localtime(&t);
        sprintf(pid, "%ld", signal.ssi_pid);
        f = fopen(pid,"a+");

        if(signal.ssi_signo == SIGUSR1){
            strcpy(message,"SIGUSR1 at ");
            strcat(message, asctime(&tt));
            fputs(message,f);
        }
        if(signal.ssi_signo == SIGUSR2){
            strcpy(message,"SIGUSR2 at ");
            strcat(message, asctime(&tt));
            fputs(message,f);
        }
        fclose(f);

    }

}