
#include <signal.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[]){
    char commands[20][5];
    char singleCommand[20], stringa[20], pid[20];
    FILE *fp;
    if(argc < 2){
        printf("Errore!\n");
        return 1;
    }
    strcpy(stringa, "/tmp/countpid");

    for(int i = 1; i < argc; i++){
        strcpy(commands[i-1], argv[i]);
    }
    fp = fopen(stringa, "r+");
    fgets(pid,sizeof(pid),fp);
    printf("%s\n", pid);
    fclose(fp);

    strcpy(singleCommand, commands[1]);
    
    return 0;
}