#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/timerfd.h>

int main(int argc, char** argv){
	int timerfd;
	int ms = atoi(argv[1]);
	if((timerfd = timerfd_create(CLOCK_MONOTONIC, 0)) == -1)
		perror("timercreate");
	uint64_t buf;
	struct itimerspec timspec;
	bzero(&timspec, sizeof(timspec));
	
	timspec.it_interval.tv_sec = 0;
	timspec.it_interval.tv_nsec = 0;
	timspec.it_value.tv_sec = 0;
	printf("%ld\n", (long)ms*1000000);
	timspec.it_value.tv_nsec = (long)ms*1000000;
	if(timerfd_settime(timerfd, 0, &timspec, 0) < 0)
		perror("settime");
	read(timerfd, &buf, sizeof(uint64_t));
	close(timerfd);
	return 0;
}
