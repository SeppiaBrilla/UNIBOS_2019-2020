#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv){
	char* path = argv[1];
	DIR* dir = opendir(path);
	struct dirent *mdir;
	struct stat statbuf;

	while(mdir = readdir(dir)){
		char pathname[64];
		time_t acc, mod;
		struct utimbuf timebuf;
		sprintf(pathname, "%s/%s", path, mdir->d_name);
		stat(pathname, &statbuf);
		acc = statbuf.st_atim.tv_sec - 10*24*60*60;
		mod = statbuf.st_mtim.tv_sec - 10*24*60*60;
		timebuf.actime = acc;
		timebuf.modtime = acc;
		utime(pathname, &timebuf);
	}
}
