/*
Lo scopo di questo esercizio è di scrivere un programma che conti quanti segnali di tipo SIGUSR1 e quanti di tipo SIGUSR2 riceve. 
Ogni volta che riceve un segnale di tipo SIGUSR1 deve aumentare un contatore di 1, ogni voltache riceve SIGUSR2 deve decrementare di 1 il contatore. 
A ogni variazione del contatore il programma stampa il valore. 
Questo programma deve essere realizzato usando la system call signalfd.
*/
#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


/* send signal with:
        kill -s SIGUSR1 pid
        kill -s SIGUSR2 pid
*/
int main(){

    sigset_t mask;
    int signal;
    int count = 0;

    printf("pid: %d \n",getpid());
    FILE *fp;
    fp  = fopen ("/tmp/countpid", "w");
    fprintf(fp, "%d", getpid());
    fclose(fp);


    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    if(sigprocmask(SIG_BLOCK, &mask, NULL) < 0){
		perror ("sigprocmask");
		return 1;
	}
    
    signal = signalfd(-1, &mask, 0);
    if (signal < 0) {
		perror ("signalfd");
		return 1;
	}

    while(1){
        struct signalfd_siginfo si;
        ssize_t res;

        res = read(signal,&si,sizeof(si));
        if (res < 0) {
			perror ("read");
			return 1;
		}
		if (res != sizeof(si)) {
			fprintf (stderr, "Something wrong\n");
			return 1;
		}
        switch (si.ssi_signo)
        {
            case SIGUSR1:
                printf("SIGUSR1!\n");
                count++;
                break;

            case SIGUSR2:
                printf("SIGUSR2!\n");
                count--;
                break;
        
            default:
                break;
        }
        printf("counter: %d\n", count);

    }

    close (signal);
    return 0;
}