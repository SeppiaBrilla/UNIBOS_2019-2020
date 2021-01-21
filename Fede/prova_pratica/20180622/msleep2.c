#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <poll.h>
#include <signal.h>
#include <sys/timerfd.h>

int main(const int argc, char** argv){
	struct pollfd fds[argc-1];
	struct itimerspec timespec[argc-1];
	int ms[argc-1];
	memset(timespec, 0, sizeof(struct itimerspec)*(argc-1));
	uint64_t buf;
	int i;
	for(i = 0; i < argc-1; i++){
		ms[i] = atoi(argv[i]);
		timespec[i].it_value.tv_nsec = (long)ms[i]*1000000;
		if((fds[i].fd = timerfd_create(CLOCK_REALTIME, 0)) == -1)
			perror("timerfd_create");
		fds[i].events = POLLIN;
	}
	i = 0;
	if(timerfd_settime(fds[0].fd, 0, &timespec[0], 0))
		perror("timerfd_settime");
	printf("here\n");
	while(i < argc-1){
		poll(fds, argc-1, -1);
		printf("now here\n");
		int j;
		for(j = 0; j < argc-1; j++){
			if(fds[j].revents == POLLIN){
				int n = read(fds[j].fd, &buf, sizeof(uint64_t));
				if(n < 0)
					perror("read");
				printf("%d\n", ms[j]);
				if((i+1) < (argc-1)){
					i++;
					if(timerfd_settime(fds[i].fd, 0, &timespec[i], 0))
						perror("timerfd_settime");
				}
			}
		}
	}
	return 0;
}
