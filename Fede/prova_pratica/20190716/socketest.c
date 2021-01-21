#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <poll.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(){
	int fd;
	struct addrinfo hints, *addr;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, "2222", &hints, &addr); 

	if((fd = socket(AF_INET, SOCK_STREAM,0)) == -1)
		perror("socket: ");
	if(bind(fd, addr->ai_addr, addr->ai_addrlen))
		perror("bind: ");
	if(connect(fd, addr->ai_addr, addr->ai_addrlen))
		perror("connect: ");
	
	struct pollfd fds[2];
	fds[0].fd = STDIN_FILENO;
	fds[1].fd = fd;

	while(1){
		poll(fds, 2, -1);
		if(fds[0].revents == POLLIN){
			char buf[BUF_SIZE];
			read(fds[0].fd, buf, BUF_SIZE);
			send(fds[1].fd, buf, BUF_SIZE, 0);	
		}
		else if(fds[1].revents == POLLIN){
			char buf[BUF_SIZE];
			recv(fds[1].fd, buf, BUF_SIZE, 0);
			write(STDOUT_FILENO, buf, BUF_SIZE);
		}
	}
		
}
	
