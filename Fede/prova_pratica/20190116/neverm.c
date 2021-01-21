#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 8
#define EVSIZE sizeof(struct inotify_event)

int main(int argc, char** argv){
	int fd, wfd;
	char* path = argv[1];
	int i;

	fd = inotify_init();
	wfd = inotify_add_watch(fd,path,IN_DELETE);
	
	for(;;){
		struct inotify_event event[BUFSIZE];
		/*funziona anche con sizeof(event)?*/
		int n = read(fd,event,sizeof(struct inotify_event)*BUFSIZE);
		for(i=0; i < (n/EVSIZE); i++){
			if(event[i].mask == IN_DELETE){
				char name[256];
				strcpy(name, path);
				strcat(name, "/");
				strcat(name, event[i].name);
				int tmpfd = open(name, O_CREAT | O_WRONLY, 0666);
				close(tmpfd);
			}
		}
	}
}
