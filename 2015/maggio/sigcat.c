/*
Esercizio 2: completamento (10 punti)
Ora, prendendo spunto dall'esercizio 1 occorre scrivere due programmi: sigsend e sigreceive.

Sigreceive non ha come parametri. Per prima cosa stampa il suo pid poi entra in un ciclo in cui:
•aspetta un segnale SIGUSR1
•stampa su stdout (visualizza) il file con nome /tmp/giroXXXX (dove XXXX e' il proprio pid)
•cancella il file /tmp/giroXXXX
•Manda un segnale SIGUSR1 al processo dal quale lo ha ricevuto nella operazione due righe sopra questa.
Sigreceive termina quando riceve in SIGUSR2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>


int main(int argc, char const* argv[]){
    sigset_t sigset;
    FILE *fptr; 
    int status, signal;
    char filename[100],buffer[10], c;

    int i = getpid();
    printf("%d\n", i);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);

    if(sigprocmask(SIG_BLOCK, &sigset, NULL) < 0){
		printf("sigprocmask\n");
		return 1;
	}
    
    signal = signalfd(-1, &sigset, 0);
    if (signal < 0) {
        perror ("signalfd");
        return 1;
    }
    while(1){
            strcpy(buffer, "");
            strcpy(filename,"");
            ssize_t res;
            struct signalfd_siginfo si;
            
            res = read(signal, &si, sizeof(si)); 
            if (res < 0) {
                perror ("read");
                return 1;
            }
            if (res != sizeof(si)) {
                fprintf (stderr, "Something wrong\n");
                return 1;
            }
            if(si.ssi_signo == SIGUSR2)
                return 0;
            if(si.ssi_signo == SIGUSR1){

                sprintf(buffer, "%d", i);
                strcpy(filename,"/tmp/giro");
                strcat(filename, buffer);
                printf("Nome del file %s\n",filename);

                fptr = fopen(filename, "r"); 
                if (fptr == NULL) 
                { 
                    printf("Cannot open file \n"); 
                    exit(0); 
                } 
                c = fgetc(fptr); 
                while (c != EOF) 
                {
                    printf("%c", c); 
                    c = fgetc(fptr); 
                } 
                printf("\n");
                fclose(fptr); 

                if (remove(filename) == 0){
                    printf("Deleted successfully\n"); 
                }
                kill(si.ssi_pid, SIGUSR1);
            }
	}
    return 0;
}