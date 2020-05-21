#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]){

    char command[100];
    char pid[6];
    if(argc >= 2){
        strcpy(command, argv[1]);
    }
    for(int i = 2; i < argc; i++){
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    FILE * fp  = fopen ("./countpid", "r");
    if(fgets(pid, 6, fp)!= NULL)
        printf("ciao");
    fclose(fp);

    if ( kill ( atoi(pid), SIGUSR1 ) == -1 )
        perror ( "Failed to send the SIGUSR2 signal" );

    system(command);

    if ( kill ( atoi(pid), SIGUSR2 ) == -1 )
        perror ( "Failed to send the SIGUSR2 signal" );

    return 0;

}
