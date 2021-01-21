#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int isinbuf(int n, int i, int* buf){
	int j;
	for(j = 0; j < i; j++){
		if(buf[j] == n)
			return 1;
	}
	printf("%d not in buf\n", n);
	return 0;
}


int main(int argc, char** argv){
	char* path =  argc >= 2 ? argv[1] : ".";
	int buf[64];
	int i = 0;
	DIR *dir = opendir(path);
	struct dirent *mdir;
	struct stat statbuf;

	while(mdir = readdir(dir)){
		int inod = mdir->d_ino;
		if(!(isinbuf(inod, i, buf)) && (mdir->d_type == DT_DIR || mdir->d_type == DT_REG)){
			buf[i] = inod;
		       	i++;
		}	
	}
	printf("Number of regular files and directories: %d\n", i);
}
