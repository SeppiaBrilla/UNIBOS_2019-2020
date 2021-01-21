#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	int i;
	int pid = atoi(argv[1]);
	for(i=2; i < argc; i++){
		if(strcmp(argv[i],"1") == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
	}
	return 0;
}
