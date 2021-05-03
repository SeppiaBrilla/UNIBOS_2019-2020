#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main(){
	int fpid, npid;
	int status;
	prctl(PR_SET_NAME, "nonno", 0, 0, 0);
	prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
	if(!(fpid = fork())){
		if(!(npid = fork())){
			prctl(PR_SET_NAME, "nipote", 0, 0, 0);
			char* nip[] = {"nipote", 0};
			execve("./nipote", nip, NULL);
		}
		prctl(PR_SET_NAME, "figlio", 0, 0, 0);
		char* fig[] = {"figlio", 0};
		execve("./figlio", fig, NULL);
	}
	sleep(2);
	kill(fpid, SIGKILL);
	printf("Figlio ucciso\n");
	waitpid(fpid, &status, 0);
	wait(&status);
	printf("Nipote terminato\n");
}
