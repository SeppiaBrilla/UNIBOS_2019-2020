#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>


#define BUF_SIZE 256

int main(int argc, char* argv[]){
	char buffer[BUF_SIZE];
	
       	DIR *dir = opendir(argv[1]);
	struct dirent *file;

	while(file = readdir(dir)){
		realpath(file->d_name, buffer);
		printf("%s\n", buffer);
	}
	return 0;
}

