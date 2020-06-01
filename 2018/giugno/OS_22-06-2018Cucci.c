/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Lo scopo di questo esercizio è di scrivere msleep. 
msleep si comporta come sleep(1) ma invece di attendere il numero di secondi indicati come parametro deve aspettare 
il numero di millisecondi indicati come parametro. es:
    msleep 2340
completa la sua esecuzione in 2340 millisecondi alias 2.34 secondi.
La msleep deve essere implementata usando i timerfd (v. timerfd_create(2)).

Esercizio 2: Linguaggio C: 10 punti
Estendere la soluzione dell'esercizio 1: 
mmsleep (multimsleep) ammette molteplici parametri.
msleep 1234 3456 2345 
allo scadere di 1234 millisecondi stampa 1234, 
allo scadere di 2345 millisecondi stampa 2345 
e infine a 3456 millisecondi dalla attivazione 
stampa 3456 ed esce.
Questo programma deve essere implementato 
creando un timerfd per ogni parametro 
e usando poll(2) per aspettare il prossimo evento.


*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <poll.h>

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("OWO, what's this?\n");
        return 1;
    }
    else
    {
        int conta = argc;
        int i = 1;
        while (conta >= 2)
        {
            int timer = timerfd_create(CLOCK_REALTIME, 0);
            int ready;
            if (timer < 0)
                handle_error("timerfd_create");

            struct itimerspec new_timer;

            int seconds = atoi(argv[i]) / 1000;
            int nseconds = atoi(argv[i]) - seconds * 1000;
            new_timer.it_value.tv_sec = seconds;
            new_timer.it_value.tv_nsec = nseconds * 1000000;
            new_timer.it_interval.tv_nsec = 0;
            new_timer.it_interval.tv_sec = 0;

            if (timerfd_settime(timer, 0, &new_timer, 0) < 0)
                handle_error("timerfd_settime");

            struct pollfd fd;
            fd.fd = timer;
            fd.events = POLLIN;
            ready = poll(&fd, 1, -1);
            printf("Aspettato per %d secondi e %d millisecondi\n", seconds, nseconds);
            if (fd.revents != POLLIN)
            {
                return 1;
            }
            conta--;
            i++;
        }
    }
    return 0;
}