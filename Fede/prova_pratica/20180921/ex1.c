#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signalfd.h>

void sig1_handler(int signo){
	printf("Received signal 1.");
}

void sig2_handler(int signo){
	printf("Recedived signal 2.");
}

int main(int argc, char** argv){
	struct pollfd fds[2];
	struct signalfd_siginfo info;

	signal(SIGUSR1, sig1_handler);
	signal(SIGUSR2, sig2_handler);

	fds[0].fd = signalfd(-1,SIGUSR1,0);
	fds[1].fd = signalfd(-1,SIGUSR2,0);
	
	for(;;){
		poll(fds, 2, -1);
		if(fds[0].revents == POLLIN){
			printf("hi\n");
			read(fds[0].fd, &info, sizeof(struct signalfd_siginfo));
			int pid = info.ssi_pid;
			time_t t = time(NULL);
			struct tm loct = *localtime(&t);
			char s[256];
			char name[8];
			sprintf(s, "SIGUSR1 %d-%02d-%02d %02d:%02d:%02d\n", loct.tm_year, loct.tm_mon+1, loct.tm_mday, loct.tm_hour, loct.tm_min, loct.tm_sec);
			sprintf(name, "%d", pid);
			int fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
			write(fd, s, 256);
			close(fd);
		}
		if(fds[1].revents == POLLIN){
			read(fds[1].fd, &info, sizeof(struct signalfd_siginfo));
			int pid = info.ssi_pid;
			time_t t = time(NULL);
			struct tm loct = *localtime(&t);
			char s[256];
			char name[8];
			sprintf(s, "SIGUSR2 %d-%02d-%02d %02d:%02d:%02d\n", loct.tm_year, loct.tm_mon+1, loct.tm_mday, loct.tm_hour, loct.tm_min, loct.tm_sec);
			sprintf(name, "%d", pid);
			int fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
			write(fd, s, 256);
			close(fd);
		}
	}
}
