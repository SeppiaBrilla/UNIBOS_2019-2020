/*
Scrivere un programma catsig che copi lo standard input nello standard output (come il comando cat senzaparametri, per intenderci) 
e che stampi la scritta “ho ricevuto un segnale” quando riceve un segnale SIGUSR1.
La particolarita' di questo programma e' che per la gestione dei segnali deve usare la chiamata di sistemasignalfd (e non la signal o la sigaction)
*/
#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>


int main(){

    int pid = fork();
    if(pid == 0){
        char str[100];
        while(1){
            scanf("%s", str);
            printf("%s\n",str);
        }
        return 0;
    }
    printf("%d\n",getpid());
    sigset_t mask;
    int signal;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    if(sigprocmask(SIG_BLOCK, &mask, NULL) < 0){
		printf ("sigprocmask");
		return 1;
	}
    signal = signalfd(-1, &mask, 0);
    if (signal < 0) {
		printf("signalfd");
		return 1;
	}
    while(1){
        struct signalfd_siginfo si ;
        ssize_t res;
        res = read(signal,&si,sizeof(si));
        if (res < 0) {
		    printf ("read");
		    return 1;
	    }
	    if (res != sizeof(si)) {
	    	printf ("Something wrong\n");
		    return 1;
	    }
        if(si.ssi_signo == SIGUSR1){
            printf("segnale ricevuto!\n");
        }

    }
    close (signal);

    return 0;

}