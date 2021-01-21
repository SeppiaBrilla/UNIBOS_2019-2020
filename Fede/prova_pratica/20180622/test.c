#include <sys/timerfd.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]){

    int timerfd = timerfd_create(CLOCK_MONOTONIC,0);
    int milliseconds = atoi(argv[1]);
    struct itimerspec timspec;
    bzero(&timspec, sizeof(timspec));
    timspec.it_interval.tv_sec = 0;
    timspec.it_interval.tv_nsec = milliseconds * 1000000;
    timspec.it_value.tv_sec = 0;
    timspec.it_value.tv_nsec = 1;

    int res = timerfd_settime(timerfd, 0, &timspec, 0);
    if(res < 0){
       perror("timerfd_settime:");
    }
    uint64_t expirations = 0;
    int iterations = 0;
    while( res = read(timerfd, &expirations, sizeof(expirations))){
        if(res < 0){ perror("read:"); continue; }
        if(expirations > 1){
            printf("%lld expirations, %d iterations\n", expirations, iterations);
            break;
        }
        iterations++;
    }
}
