/*
scrivere un programma para per lanciare parallelamente comandi

para sleep 20 // ls -l // ps // sleep 3

deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
*/
// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>

// int main(int argc, char * argv[]){

//     char commands[10][50];
//     int commandindex=0;
//     int status;

//     for(int i = 0; i< 10; i++){
//         strcpy(commands[i], "");
//     }

//     for(int i = 1; i< argc; i++){
//         if(strcmp(argv[i], "//")==0){
//             commandindex++;
//         }else{
//             strcat(commands[commandindex],argv[i]);
//             strcat(commands[commandindex], " ");
//         }
//     }    
    
//     int pid[commandindex];

//     for(int i = 0; i<= commandindex; i++){
//         pid[i] = fork();
//         if(pid[i] == 0){
//             system(commands[i]);
//             printf("processo %d completato\n", getpid());
//             return 0;
//         }else{
//             printf("processo %d lanciato\n", pid[i]);
//         }
//     }

//     while (wait(&status) > 0);
//     printf("finito!\n");
//     return 0;
// }



//parte 2
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    char commands[10][50];
    int commandindex=0;
    int status;
    int maxcommands = 0;
    int current = 0;

    if(!(maxcommands = atoi(argv[1]))){
        printf("error");
        return 1;
    }
    for(int i = 0; i< 10; i++){
        strcpy(commands[i], "");
    }

    for(int i = 2; i< argc; i++){
        if(strcmp(argv[i], "//")==0){
            commandindex++;
        }else{
            strcat(commands[commandindex],argv[i]);
            strcat(commands[commandindex], " ");
        }
    }

    int pid[commandindex];
    
    for(int i = 0; i<= commandindex; i++){
        if(current==maxcommands){
            wait(&status);
            current --;
        }
        pid[i] = fork();
        if(pid[i] == 0){
            system(commands[i]);
            printf("processo %d completato\n", getpid());
            return 0;
        }else{
            current++;
            printf("processo %d lanciato\n numero processi = %d\n", pid[i], current);
        }
    }

    while (wait(&status) > 0);

    printf("finito!\n");
    return 0;
}