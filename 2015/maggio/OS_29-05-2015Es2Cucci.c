#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>

/*
/*
Sigsend ha come parametro il pid del processo ricevente. 
Per ogni riga posta in input da stdin fa le seguenti azioni:
•crea un file /tmp/giroXXXX (dove XXXX e' il pid del processo ricevente), vi scrive la riga letta e lo chiude.
•Spedisce un segnale SIGUSR1 al ricevente
•Aspetta dallo stesso un SIGUSR1. Quando lo stdin termina (^D da tastiera) manda un SIGUSR2 al ricevente.
All'attivazione scrive nel file il proprio pid e aspetta un segnale sigusr1.Quando riceve il segnale legge 
Anche in questo esercizio occorre usare solo la signalfd e non la signal o la sigaction.
*/

int main(int argc, char const* argv[]){
    sigset_t sigset;
    FILE *fptr; 
    int status, signal;
    int sender_pid = atoi(argv[1]);
    ssize_t res;
    struct signalfd_siginfo si;
    char filename[100],buffer[10], stringa[100], linea[20];

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);

    if(sigprocmask(SIG_BLOCK, &sigset, NULL) < 0){
		printf("sigprocmask\n");
		return 1;
	}
    
    signal = signalfd(-1, &sigset, 0);
    if (signal < 0) {
        perror ("signalfd");
        return 1;
    }

    sprintf(buffer, "%d", sender_pid);
    strcpy(filename,"/tmp/giro");
    strcat(filename, buffer);
    printf("Nome del file %s\n",filename);
    
    while (1) {
        scanf("%s", stringa);
        if (feof(stdin)){
            kill(sender_pid, SIGUSR2);
            return 0;
        }
        else{
            fptr = fopen(filename, "w+"); 
            fputs(stringa, fptr);
            fclose(fptr);

            kill(sender_pid, SIGUSR1);

            res = read(signal, &si, sizeof(si)); 
        }
    }

    return 0;
}