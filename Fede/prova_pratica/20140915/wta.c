#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <execs.h>

#define BUFSIZE 64
#define MAXCMD	8

int main(int argc, char** argv){
	FILE *f = fopen(argv[1], "r");
	char* cmds[MAXCMD];
	pid_t pids[MAXCMD];
	int i = 0, j;
	int status;	
	
	cmds[i] = (char*)malloc(BUFSIZE);
	while(fgets(cmds[i], BUFSIZE, f))
		cmds[++i] = (char*)malloc(BUFSIZE);
	
	for(j = 0; j < i; j++){
		if(!(pids[j] = fork())){
			if(execsp(cmds[j]))
				perror("execsp");
		}
	}
	wait(&status);
	for(j = 0; j < i; j++){
		kill(pids[j], SIGTERM);
	}
	return 0;
}
