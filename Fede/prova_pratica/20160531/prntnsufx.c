#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

int sufxcmp(const void* arg1, const void* arg2){
	int val1, val2;
	const char *f1 = *(const char**)arg1, *f2 = *(const char**)arg2;
	printf("%s %s\n", *(const char**)arg1, *(const char**)arg2);
	size_t len;
	char buf[128];
	int i,j;
	int pos;

	len = strlen(f1);
	for(i = len-1; i >= 0; i--){
		if(f1[i] == '.')
			break;
	}
	pos = i;
	j = 0;
	for(i = pos+1; i < len; i++){
		buf[j] = f1[i];
		j++;	
	}
	buf[j] = '\0';
	val1 = atoi(buf);

	len = strlen(f2);
	for(i = len-1; i >= 0; i--){
		if(f2[i] == '.')
			break;
	}
	pos = i;
	j = 0;
	for(i = pos+1; i < len; i++){
		buf[j] = f2[i];
		j++;	
	}
	buf[j] = '\0';
	val2 = atoi(buf);
	
	if(val1 == val2){
		printf("%d = %d\n", val1, val2);
		return 0;
	}
	if(val1 > val2){
		printf("%d > %d\n", val1, val2);
		return 1;
	}
	if(val1 < val2){
		printf("%d < %d\n", val1, val2);
		return -1;
	}
}

int main(int argc, char** argv){
	char* path = argc >= 2 ? argv[1] : ".";
	DIR* dir = opendir(path);
	struct dirent* mydir;
	char* fnames[128];
	int fcounter = 0;
	int i;

	while(mydir = readdir(dir)){
		if(mydir->d_type != DT_DIR){
			size_t len = strlen(mydir->d_name);
			for(i = len-1; i >= 0; i--){	
				if(!isdigit(mydir->d_name[i]))
					break;
			}
			if(mydir->d_name[i] == '.' && i != len-1){
				fnames[fcounter] = malloc(sizeof(len));
				strcpy(fnames[fcounter], mydir->d_name);
				fcounter++;
			}
		}
	}
	printf("%d\n", fcounter);
	char** tosort = malloc(fcounter*sizeof(char*));
	for(i = 0; i < fcounter; i++){
		int len = strlen(fnames[i]);
		tosort[i] = (char*)malloc(len);
		strcpy(tosort[i], fnames[i]);
	}
	printf("%d %d %d\n", sizeof(tosort), sizeof(char*), sizeof(tosort)/sizeof(char*));
	
	qsort(tosort, fcounter, sizeof(char*), sufxcmp); 
	for(i = 0; i < fcounter; i++){
		printf("%s\n", fnames[i]);
	}
}
