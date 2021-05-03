#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUF_SIZE 64
#define MAX_ARGS 8

int main(int argc, char** argv){
	int i, j, k;
	int status;
	int pidv[MAX_ARGS];
	char* cmd[MAX_ARGS];
	for(i = 0; i < MAX_ARGS; i++)
		pidv[i] = 0;
	
	j = k = 0;
	i = 1;
	while(i < argc){
		if(strcmp(argv[i], "//") != 0){
			cmd[j] = argv[i];
			j++;	
		}
		else{	
			char bin[BUF_SIZE] = "/bin/";
			strcat(bin, cmd[0]);
			cmd[j] = 0;
			if(!(pidv[k] = fork())){
				if(execve(bin, cmd, NULL))
					perror("exec: ");
			}
			k++;
			j = 0;
		}
		i++;
	}
	char bin[BUF_SIZE] = "/bin/";
	strcat(bin, cmd[0]);
	cmd[j] = 0;
	if(!(pidv[k] = fork())){
		if(execve(bin, cmd, NULL))
			perror("exec: ");
	}
	
	i = 0;
	while(i < MAX_ARGS && pidv[i] != 0){
		waitpid(pidv[i], &status, 0);
		i++;
	}

	return 0;

}
