#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/types.h>

#define BUFSIZE 512

int main(int argc, char** argv){
	char *path1 = argv[1], *path2 = argv[2];
	int fd1, fd2;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	off_t l_start = 0;
	off_t l_len = -1;
	pid_t l_pid = getpid();
	fd1 = open(path1, O_RDONLY);
	fd2 = open(path2, O_WRONLY);
	
	while((fcntl(fd2, F_SETLK, &lock)) == -1){
		printf("File already locked.\n");
		sleep(3);
	}
	printf("Acquired file lock.\n");
	if((sendfile(fd2, fd1, 0, BUFSIZE) == -1))
		perror("sendfile");
	sleep(3);
	lock.l_type = F_UNLCK;
	fcntl(fd2, F_SETLK, &lock);
	printf("File lock released.\n");
	return 0;
}
