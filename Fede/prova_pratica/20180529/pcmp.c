#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv){
	char *path1 = argv[1], *path2 = argv[2];
	int length1, length2, len11, len12, len21, len22;
	int pid1, pid2;
	int status;
	int fd = open(path1, O_RDONLY);
	length1 = lseek(fd, 0, SEEK_END);
	close(fd);
	len11 = length1/2;
	len12 = length1-len11;
	fd = open(path2, O_RDONLY);
	length2 = lseek(fd, 0, SEEK_END);
	close(fd);
	len21 = length2/2;
	len22 = length2-len21;

	if(!(pid1 = fork())){
		int fd1 = open(path1, O_RDONLY);
		int fd2 = open(path2, O_RDONLY);
		char buf1, buf2;
		int counter = 0;
		while(counter <= len11 && counter <= len21 && buf1 != EOF){
			read(fd1, &buf1, sizeof(char));
			read(fd2, &buf2, sizeof(char));
			printf("1: %c %c\n", buf1, buf2);
			if(buf1 != buf2){
				printf("Difference in part 1\n");
				return 1;
			}
			counter++;
		}
		return 0;
	}
	if(!(pid2 = fork())){
		int fd1 = open(path1, O_RDONLY);
		int fd2 = open(path2, O_RDONLY);
		lseek(fd1, len11+1, 0);
		lseek(fd2, len21+1, 0);
		char buf1, buf2;
		int counter = 0;
		while(counter <= len12 && counter <= len22 && buf1 != EOF){
			read(fd1, &buf1, sizeof(char));
			read(fd2, &buf2, sizeof(char));
			printf("2: %c %c\n", buf1, buf2);
			if(buf1 != buf2){
				printf("Difference in part 2\n");
				return 1;
			}
			counter++;
		}
		return 0;
	}
	int i;
	for(i = 0; i < 2; i++){
		waitpid(-1, &status, 0);
		printf("Status%d: %d\n", i+1, WEXITSTATUS(status));
		if(WEXITSTATUS(status) == 1){
			printf("Different.\n");
			exit(1);
		}
	}
	printf("Same.\n");
	return 0;
}
