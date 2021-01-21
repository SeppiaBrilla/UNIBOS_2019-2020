#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpfnc(const void* arg1, const void* arg2){
	printf("%s %s\n", *(const char**)arg1, *(const char**)arg2);
	
	return strcmp(*(const char**)arg1, *(const char**)arg2);
}

int main(){
	char* words[] = {"ciao", "prova", "mare", "spiaggia", "albero"};
	int i;
	printf("%d %d %d\n", sizeof(words), sizeof(char*), sizeof(words)/sizeof(char*));
	size_t arrlen = sizeof(words)/sizeof(char*);
	qsort(words, arrlen, sizeof(char*), cmpfnc);
	for(i = 0; i < sizeof(words)/sizeof(char*); i++)
		printf("%s\n", words[i]);
}
