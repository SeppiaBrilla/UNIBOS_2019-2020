#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ever ;;
#define BUFSIZE 8

int main(int argc, char** argv){
	int fd, wfd;
	char* dir = argv[1];
	DIR *d = opendir(dir);
	struct dirent *myd;
	int i = 0;
	int n;
	while(myd = readdir(d))
		i++;
	if(i > 2){
		printf("Directory is not empty.\n");
		exit(1);
	}	
	fd = inotify_init();
	wfd = inotify_add_watch(fd, dir, IN_CREATE | IN_MOVED_TO);
	for(ever){
		void* buf = malloc(sizeof(struct inotify_event)*BUFSIZE);
		n=read(fd,buf,sizeof(struct inotify_event)*BUFSIZE);
		printf("%d\n",n);
		for(i=0; i < n/sizeof(struct inotify_event); i++){
			struct inotify_event *event = (struct inotify_event*)&buf[i];
			if(event->mask == IN_CREATE || event->mask == IN_MOVED_TO){
				int pid;
				char path[256] = "";
				int status;
				strcat(path, dir);
				strcat(path, "/");
				strcat(path, event->name);
				printf("%s\n", path);
				if(!(pid = fork())){
					if(execve(path,0,0))
						perror("execve: ");
				}
				waitpid(pid, &status, 0);
				remove(path);
			}

		}
		free(buf);
	}
	return 0;
}
