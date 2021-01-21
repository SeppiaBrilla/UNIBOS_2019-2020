#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUF_SIZE 256

int main(int argc, char** argv){
	char* cmd1[] = {"ls", "-l", 0};
	char* cmd2[] = {"sleep", "5", 0};
	char* cmd3[] = {"ps", 0};

	char** cmd[3];
	cmd[0] = cmd1;
	cmd[1] = cmd2;
	cmd[2] = cmd3;
	int status[3];
	int pidv[3];
	int i;
	for(i = 0; i < 3; i++){
		if(!(pidv[i] = fork())){
		char buf[BUF_SIZE] = "/bin/";
		strcat(buf, cmd[i][0]);
		printf("%s\n", buf);
		if(execve(buf, cmd[i], NULL))
			perror("execve: ");
			exit(1);
		}
	}
	for(i = 0; i < 3; i++)
		waitpid(pidv[i], &status[i], 0);

	return 0;

}
