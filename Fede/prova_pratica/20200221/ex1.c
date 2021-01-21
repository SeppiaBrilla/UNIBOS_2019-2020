#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char* argv[]){
	char buffer[BUF_SIZE];
	char* path = realpath(argv[1], buffer);
	symlink(path, argv[1]); 
	return 0;
}
