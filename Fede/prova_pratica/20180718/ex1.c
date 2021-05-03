#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <poll.h>
#include <unistd.h>
#include <sys/signalfd.h>

#define BUFSIZE 8
#define INFOSIZE sizeof(struct signalfd_siginfo)

int main(int argc, char** argv){
	struct pollfd fds[2];
	sigset_t set1, set2;
	int i, n;
	int counter = 0;

	sigemptyset(&set1);
	sigemptyset(&set2);
	sigaddset(&set1, SIGUSR1);
	sigaddset(&set2, SIGUSR2);
	sigprocmask(SIG_BLOCK, &set1, NULL);
	sigprocmask(SIG_BLOCK, &set2, NULL);
	fds[0].fd = signalfd(-1, &set1, 0);
	fds[1].fd = signalfd(-1, &set2, 0);
	fds[0].events = POLLIN;
	fds[1].events = POLLIN;
	
	for(;;){
		poll(fds, 2, -1);
		if(fds[0].revents == POLLIN){
			struct signalfd_siginfo info[BUFSIZE];
			n = read(fds[0].fd, info, BUFSIZE*INFOSIZE);
			for(i = 0; i < n/INFOSIZE; i++){
				counter++;
				printf("Counter is: %d\n", counter);
			}
		}
		if(fds[1].revents == POLLIN){
			struct signalfd_siginfo info[BUFSIZE];
			n = read(fds[1].fd, info, BUFSIZE*INFOSIZE);
			for(i = 0; i < n/INFOSIZE; i++){
				counter--;
				printf("Counter is: %d\n", counter);
			}
		}
	}
}
