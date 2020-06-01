/* 
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Lo scopo di questo esercizio è di scrivere un programma, 
che usando la system call signalfd quando riceve un segnale SIGUSR1 o SIGUSR2, 
scriva in un file della directory corrente con nume uguale al pid del processo che ha inviato il segnale, 
il tipo di segnale ricevuto e l'ora esatta di ricezione del segnale. 
(se il file non esiste deve essere creato).
un esempio di file risultante potrebbe essere:
$ cat 20231
USR1 Fri Sep 21 10:40:56 CEST 2018
USR1 Fri Sep 21 10:40:58 CEST 2018
USR2 Fri Sep 21 10:41:26 CEST 2018
*/
/*
#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    sigset_t mask;
    int sfd;
    FILE *fp;

    printf("pid: %d \n", getpid());

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
    {
        perror("sigprocmask");
        return 1;
    }

    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1)
    {
        perror("signalfd");
        return 1;
    }

    while (1)
    {
        ssize_t c;
        struct signalfd_siginfo inserimento;
        c = read(sfd, &inserimento, sizeof(struct signalfd_siginfo));

        if (c < 0)
        {
            perror("read");
            return 1;
        }
        if (c != sizeof(inserimento))
        {
            fprintf(stderr, "Something wrong\n");
            return 1;
        }

        if (inserimento.ssi_signo == SIGUSR1 || inserimento.ssi_signo == SIGUSR2)
        {
            char name[20];
            sprintf(name, "%d", inserimento.ssi_pid);
            char tp[20];
            strcpy(tp, "./");
            strcat(tp, name);
            if (!(fp = fopen(tp, "a")))
            {
                printf("error!\n");
                return 1;
            }
            struct tm *ptr;
            time_t t = time(NULL);
            ptr = localtime(&t);
            if (inserimento.ssi_signo == SIGUSR1)
                fprintf(fp, "SIGUSR1 %s", asctime(ptr));
            else if (inserimento.ssi_signo == SIGUSR2)
                fprintf(fp, "SIGUSR2 %s", asctime(ptr));
            fclose(fp);
        }
    }
    return 0;
}
*/

/*
Esercizio 2: Linguaggio C: 10 punti
Dato un estratto di un file di log come questo:

Sep 20 19:58:32 eipi ntpd[2051]: Listen normally on 99 eth0 [fe80::8456:a70]:123
Sep 20 19:58:32 eipi ntpd[2051]: new interface(s) found: waking up resolver
Sep 20 19:58:34 eipi ntpd[2051]: Soliciting pool server 151.3.106.211
Sep 20 19:58:35 eipi ntpd[2051]: Soliciting pool server 94.177.187.22
Sep 20 19:58:48 eipi ntpd[2051]: Soliciting pool server 80.211.155.206
Sep 20 19:58:49 eipi ntpd[2051]: Soliciting pool server 212.45.144.206

Scrivere un programma che lo mostri alla stessa velocita' allla quale e' stato generato.
In questo caso dovrebbe scrivere le prime dur righe, attendere 2 secondi, mostrare la terza, 
dopo un secondo la quarta quindi dopo una attesa di 13 secondi la quinta e la sesta dopo un ulteriore secondo.
*/
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    char *word;
    struct tm time[50];
    char command[50][100];
    char linee[500];
    int i = 0;
    int x = 0;

    FILE *fp = fopen(argv[1], "r+");

    while (fgets(linee, sizeof(linee), fp))
    {
        i = 0;
        word = strtok(linee, " ");
        while (word != NULL)
        {
            if (i == 0)
            {
                time[x].tm_mon = atoi(word);
            }
            else if (i == 1)
            {
                time[x].tm_mday = atoi(word);
            }
            else if (i == 2)
            {
                char *d;
                int j = 0;
                d = strtok(word, ":");
                while (d != NULL)
                {
                    if (j == 0)
                    {
                        time[x].tm_hour = atoi(d);
                    }
                    else if (j == 1)
                    {
                        time[x].tm_min = atoi(d);
                    }
                    else if (j == 2)
                    {
                        time[x].tm_sec = atoi(d);
                    }
                    d = strtok(word, ":");
                    j++;
                }
            }
            strcat(command[x], word);
            word = strtok(NULL, " ");
            i++;
        }
    }
    for (int k = 0; k < x; k++)
    {
        printf("comando n.%d ad ora %s: %s\n", k, asctime(&time[x]), command[k]);
    }
}*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int ritard = 0;
    char *month[50];
    int day[50];
    char *time[50];
    int hour[50];
    int minutes[50];
    int seconds[50];
    char linee[500];
    int i = 0;

    FILE *fp = fopen(argv[1], "r+");

    while (fgets(linee, sizeof(linee), fp))
    {
        sleep(ritard);
        printf("%s\n", linee);
        month[i] = strtok(linee, " ");
        day[i] = atoi(strtok(NULL, " "));
        time[i] = strtok(NULL, " ");
        hour[i] = atoi(strtok(time[i], ":"));
        minutes[i] = atoi(strtok(NULL, ":"));
        seconds[i] = atoi(strtok(NULL, ":"));

        if (i > 0)
        {
            ritard = 0;
            /*if (month[i] > month[i-1])
                ritard = ritard + (atoi(month[i]) - atoi(month[i-1]) * 24 * 60 *60 *60 );*/
            if (day[i] > day[i - 1])
                ritard = ritard + (day[i] - day[i - 1] * 60 * 60 * 60);
            if (hour[i] > hour[i - 1])
                ritard = ritard + (hour[i] - hour[i - 1] * 60 * 60);
            if (minutes[i] > minutes[i - 1])
                ritard = ritard + (minutes[i] - minutes[i - 1] * 60);
            if (seconds[i] > seconds[i - 1])
                ritard = ritard + (seconds[i] - seconds[i - 1]);     
        }

        i++;
    }

    return 0;
}
