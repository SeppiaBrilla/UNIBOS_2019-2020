/*
Lo scopo di questo esercizio è di scrivere msleep. 
msleep si comporta come sleep(1) ma invece di attendere il numero di secondi indicati come parametro deve aspettare il numero di millisecondi indicati come parametro.
es:
    msleep 2340
completa la sua esecuzione in 2340 millisecondi alias 2.34 secondi.
La msleep deve essere implementata usando i timerfd (v. timerfd_create(2)).
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <poll.h>

//1 ms = 1000000 nanosec

int main(int argc, char * argv[]){

    if(argc < 2)
        return 1;

    for(int i = 1; i < argc; i++){
        int timer = timerfd_create(CLOCK_REALTIME, 0);
        if(timer < 0)
            return 1;
        uint64_t buff;
        struct itimerspec nv;
        struct itimerspec ov;
        int seconds = atoi(argv[i])/1000;
        int nseconds = atoi(argv[i]) - seconds * 1000;
        printf("waiting for %d seconds and %d milliseconds \n", seconds, nseconds);
        nv.it_value.tv_sec = seconds;
        nv.it_value.tv_nsec = nseconds * 1000000;
        nv.it_interval.tv_nsec = 0;
        nv.it_interval.tv_sec = 0;
        if(timerfd_settime(timer, 0, &nv, 0) < 0)
            return 1;
        //read(timer,&buff,sizeof(uint64_t));
        struct pollfd poll_f;
        poll_f.fd = timer;
        poll_f.events = POLLIN;
        poll(&poll_f,1, atoi(argv[i])* 2);
        if(poll_f.revents != POLLIN){
            printf("error accoured");
            return 1;
        }
        printf("time %d seconds and %d milliseconds up!\n",seconds,nseconds);
    }
    
    printf("done!\n");


    return 0;
}