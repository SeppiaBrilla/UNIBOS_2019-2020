#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execs.h>

#define BUFLEN 1024

int main(){
	char buf[BUFLEN];
	printf("C Example Shell. Logout or ^D to quit.\n");
	for(;;){
		if(fgets(buf, BUFLEN, stdin) != NULL && (strcmp(buf, "logout") != 0)){
			if(!fork())
				execsp(buf);
		}
		else break;
	}
	printf("Exiting...\n");
}
