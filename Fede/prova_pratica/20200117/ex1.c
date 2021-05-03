#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

int recdir(char *path, ino_t finode){
	char* buf[BUF_SIZE];
	DIR *d = opendir(path);
	struct dirent* dirf;
	struct stat st;
	if(!d)
		return 1;
	char newpath[BUF_SIZE];

	while(dirf = readdir(d)){
		if(strcmp(dirf->d_name,".") != 0 && strcmp(dirf->d_name,"..")!= 0){
			lstat(dirf->d_name, &st);
			if(st.st_ino == finode)
				printf("link %s/%s\n", path, dirf->d_name);
			else if(st.st_mode == S_IFLNK){
				stat(dirf->d_name, &st);
				//if(st.st_ino == finode)
					printf("symlink %s/%s\n", path, dirf->d_name);
			}
			snprintf(newpath, BUF_SIZE, "%s/%s/", path, dirf->d_name);
			recdir(newpath, finode);
		}
	}
}

int main(int argc, char** argv){
	struct stat st;
	stat(argv[1], &st);
	recdir(argv[2], st.st_ino);
	return 0;
}
